#pragma once

#include <unordered_map>
#include "auxiliary_classes.h"
#include "node.h"
#include "link.h"

class city_builder {
private:
	std::vector<linkId> links_id;
	std::vector<nodeId> nodes_id;
	std::unordered_map<linkId, link> links;
	std::unordered_map<nodeId, node> nodes;

	std::unordered_map<nodeId, std::vector<std::pair<nodeId, linkId>>> connected_nodes_info;

public:
	void make_node(nodeId id, double x, double y);
	void make_link(linkId id, std::pair<nodeId, nodeId> ends, double width, double distance);
	void make_link(linkId id, std::pair<nodeId, nodeId> ends, double width);

	std::unordered_map<linkId, link> get_links(void);
	std::unordered_map<nodeId, node> get_nodes(void);
	std::vector<linkId> get_links_id(void);
	std::vector<nodeId> get_nodes_id(void);
	std::unordered_map<nodeId, std::vector<std::pair<nodeId, linkId>>> get_connected_nodes_info(void);
};