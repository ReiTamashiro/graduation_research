#pragma once
#include "agent.h"
#include "city.h"
#include <array>
#include <iostream>
#include <variant>

linkId whats_link(const city map, nodeId current, nodeId next) {
	for (auto x : map.connected_nodes_info.at(current)) {
		if (x.first == next) {
			return x.second;
		}
	}
	throw;
}

std::vector<nodeId> nodes_subset(std::vector<nodeId> s1, std::vector<nodeId> s2) {
	std::vector<nodeId> res;
	for (auto one : s1) {
		auto fun = [](const nodeId some, const std::vector<nodeId> visiteds) -> bool {
			for (auto visited : visiteds) {
				if (visited == some) {
					return true;
				}
			}
			return false;
		};
		if (fun(one, s2) == false) {
			res.emplace_back(one);
		}
	}
	return res;
}

std::vector<nodeId> get_passable_route(const city map,const nodeId current, const std::unordered_map<linkId, bool> passability){
	std::vector<nodeId> res;
	for (auto x : map.connected_nodes_info.at(current)) {
		if (passability.at(x.second)) {
			res.push_back(x.first);
		}
	}
	return res;
}

std::vector<nodeId> get_connect_nodes(const city map, nodeId origin) {
	std::vector<nodeId> res = {};
	for (auto x : map.connected_nodes_info.at(origin)) {
		res.emplace_back(x.first);
	}
	return res;
}

using search = std::variant<std::string, std::pair<double, std::vector<nodeId>>>;

class searching {
	search minimum_route = "";
	double minimum_cost = 100000;

public:
	const city map;
	const std::unordered_map<linkId, unsigned int> traffic;
	const std::unordered_map<linkId, bool> passability;
	const nodeId current;
	const nodeId target;	

	searching(city map, const std::unordered_map<linkId, unsigned int> traffic, const std::unordered_map<linkId, bool> passability, nodeId current, nodeId target) : map(map),traffic(traffic), passability(passability), current(current), target(target) {};
	
	search get_route() {
		return this->minimum_route;
	}

	void calculate_cost_rc(const std::vector<nodeId> visited, double cumulative_cost) {

		if (cumulative_cost > minimum_cost) {
			return;
		}

		for (auto x : nodes_subset(get_passable_route(map, visited.back(), passability), visited)) {
			std::vector<nodeId> res = visited;
			res.push_back(x);
			auto cost = cumulative_cost + (map.links.at(whats_link(map, visited.back(), x)).distance / 1.742);
			if (x == target) {
				if (cost <= minimum_cost) {
					minimum_route = std::make_pair(cost, std::move(res));
					minimum_cost = std::get<std::pair<double, std::vector<nodeId>>>(minimum_route).first;
				}
			}
			else {
				calculate_cost_rc(std::move(res), cost);
			}
		}
	}

	search calculate_cost() {
		for (auto connected : get_connect_nodes(map, current)) {
			std::vector<nodeId> con = { current, connected };
			link current_link = map.links.at(whats_link(map, current, connected));
			double cost = current_link.distance / (1.742 - (traffic.at(current_link.id) / (current_link.distance * current_link.width) * 0.343));
			if (connected == target) {
				if (cost <= minimum_cost) {
					minimum_route = std::make_pair(cost, con);
					minimum_cost = std::get<std::pair<double, std::vector<nodeId>>>(minimum_route).first;
				}
			}
			calculate_cost_rc(con, cost);
		}

		return minimum_route;
	}

};


id_had_agent agent::get_identifications(void) {
	return this->identifications;
}

void agent::move(const city belong, const std::unordered_map<linkId, unsigned int> traffic, const std::unordered_map<linkId, bool> passability){
	if (this->state == state_agent::ARRIVAL || this->state == state_agent::FAILED) {
		return;
	}
	if (this->state == state_agent::MOVE) {
		auto current = belong.links.at(this->identifications.link_current);
		auto next = belong.nodes.at(this->identifications.node_next);
		auto prev = belong.nodes.at(this->identifications.node_previous);
		
		double speed = 1.742 - (traffic.at(current.id) / (current.distance * current.width) * 0.343);
		this->position += speed;

		if ((this->identifications.shelter_target == next.id && this->position >= current.distance) || ((this->identifications.shelter_target == prev.id) && (this->position == 0))) {
			this->state = state_agent::ARRIVAL;
			this->position = 0;
			return;
		}
		
		if (this->position >= current.distance) {
			double excess = this->position - current.distance;
			excess = excess + (traffic.at(current.id) / (current.distance * current.width) * 0.343);

			//calculate costs
			//next node Decision
			auto searched = searching(belong, traffic, this->knowledge_link_passability, next.id, this->identifications.shelter_target);
			searched.calculate_cost();
			//auto routes = calculation_cost_stub(belong, passability, next.id, this->identifications.shelter_target);
			auto routes = searched.get_route();
			if (routes.index() == 0) {
				this->state = state_agent::FAILED;
				return;
			}
			else if (routes.index() == 1){
				this->evacuation_route = std::get<std::pair<double, std::vector<nodeId>>>(routes).second;
			}
			
			this->identifications.node_previous = this->evacuation_route.at(0);
			this->identifications.node_next = this->evacuation_route.at(1);

//			std::cout << this->identifications.node_previous.c_str() << ":" << this->identifications.node_next.c_str() << std::endl;

			this->identifications.link_current = whats_link(belong, this->identifications.node_previous, this->identifications.node_next);
			//inverse position , swap(prev, next)

			this->position = std::max(excess - (traffic.at(current.id) / (current.distance * current.width) * 0.343), 0.1);
		}
		
		//target Arrived
		if ((this->identifications.shelter_target == next.id && this->position == current.distance) || ((this->identifications.shelter_target == prev.id) && (this->position == 0))) {
			this->state = state_agent::ARRIVAL;
			return;
		}
	}
}


