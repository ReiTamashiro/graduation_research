#include "simulator.h"

void simulator::startup() {
	this->step++;

	for (auto agent : this->agents) {
		this->link_traffic.at(agent->get_identifications().link_current)++;
	}
	
	for (auto agent : this->agents) {
		agent->move(this->map, this->link_traffic, this->link_passability);
	}

	for (auto i : this->map.links_id) {
		this->link_traffic.at(i) = 0;
	}
}

std::vector<agent> simulator::get_agents() {
	std::vector<agent> res;
	for (auto x : this->agents) {
		res.push_back(*x);
	}
	return res;
};