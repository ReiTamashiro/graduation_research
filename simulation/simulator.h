#pragma once
#include "auxiliary_classes.h"
#include "city.h"
#include "agent.h"
#include <memory>

class simulator {
private:
	unsigned int step = 0;
	std::unordered_map<linkId, unsigned int> link_traffic;
	std::unordered_map<linkId, bool> link_passability;
	std::unordered_map<nodeId, shelter> shelter_traffic;
	std::vector<std::shared_ptr<agent>> agents;

public:
	const city map;

	simulator(const city map, std::vector<std::shared_ptr<agent>> agents) : map(map), agents(agents){
		std::vector<nodeId> shells = {"A", "B", "C"};
		shelter shell = shelter(100);
		for (auto id: map.links_id) {
			this->link_traffic.insert(std::make_pair(id, 0));
			this->link_passability.insert(std::make_pair(id, true));
		}
		for (auto id : shells) {
			this->shelter_traffic.insert(std::make_pair(id, shell));
		}

		for (auto x : agents) {
			link_traffic.at(x->get_identifications().link_current)++;
		}
	};
	void startup();
	//std::vector<std::shared_ptr<agent>> get_agents() { return this->agents; };
	std::vector<agent> get_agents();
	unsigned int get_step() { return this->step; };
};