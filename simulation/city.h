#pragma once

#include <unordered_map>
#include <string>

#include "auxiliary_classes.h"
#include "auxiliary_function.h"
#include "link.h"
#include "node.h"
#include "city_builder.h"

struct city {
public:
	const std::vector<linkId> links_id;
	const std::vector<nodeId> nodes_id;
	const std::unordered_map<linkId, link> links;
	const std::unordered_map<nodeId, node> nodes;

	const std::unordered_map<nodeId, std::vector<std::pair<nodeId, linkId>>> connected_nodes_info;

	city(city_builder *init) : links_id(init->get_links_id()), nodes_id(init->get_nodes_id()), links(init->get_links()), nodes(init->get_nodes()), connected_nodes_info(init->get_connected_nodes_info()){};

	static linkId search_next_link(const city* city, nodeId current, nodeId next);
};

