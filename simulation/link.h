#pragma once

#include "auxiliary_classes.h"

struct link{
	const linkId id;
	const double width, distance;
	const std::pair <nodeId , nodeId> ends;

	link(linkId id, double width, double distance, std::pair<nodeId, nodeId> ends) : id(id), width(width), distance(distance), ends(ends) {};
	bool is_exists(nodeId id);
};