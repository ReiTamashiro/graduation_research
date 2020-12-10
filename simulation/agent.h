#pragma once
#include "auxiliary_classes.h"
#include "auxiliary_function.h"

#include "link.h"
#include "node.h"
#include "city.h"

std::pair<double, const std::vector<nodeId>> calculate_cost(const city map);

class agent{
private:
	double position;
	state_agent state = state_agent::MOVE;
	id_had_agent identifications;
	route evacuation_route;
	std::vector<nodeId> shelter_node;
	std::unordered_map<nodeId, double> knowledge_shelter_traffic;
	std::unordered_map<linkId, bool> knowledge_link_passability;

public:
	const agentId id;

	agent(city map, id_had_agent identifications, double position, route route) : id(get_unique_id()) {
		for (auto link_id : map.links_id) {
			knowledge_link_passability.insert(std::make_pair(link_id, true));
		}
		this->identifications = identifications;
		this->evacuation_route = route;
		this->position = position;
	};

	id_had_agent get_identifications(void);
	void move(const city belong, const std::unordered_map<linkId, unsigned int> traffic, const std::unordered_map<linkId, bool> passability);
	double get_position() { return this->position; };
	state_agent get_state() { return this->state; };
};