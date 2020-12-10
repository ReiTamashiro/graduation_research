#pragma once
#include "city_builder.h"

std::vector<linkId> city_builder::get_links_id(void) {
	return this->links_id;
}

std::vector<nodeId> city_builder::get_nodes_id(void) {
	return this->nodes_id;
}

std::unordered_map<linkId, link> city_builder::get_links(void) {
	return this->links;
}

std::unordered_map<nodeId, node> city_builder::get_nodes(void) {
	return this->nodes;
};

std::unordered_map<nodeId, std::vector<std::pair<nodeId, linkId>>> city_builder::get_connected_nodes_info(void) {
	return this->connected_nodes_info;
}

void city_builder::make_node(nodeId id, double x, double y) {
	std::vector<std::pair<nodeId, linkId>> empty;
	this->nodes_id.push_back(id);
	this->nodes.insert(std::make_pair(id, node(id, x, y)));
	this->connected_nodes_info.insert(std::make_pair(id, empty));
}

void city_builder::make_link(linkId id, std::pair<nodeId, nodeId> ends, double width, double distance) {
	auto first = this->nodes.at(ends.first);
	auto second = this->nodes.at(ends.second);

	this->connected_nodes_info.at(ends.first).emplace_back(std::make_pair(ends.second, id));
	this->connected_nodes_info.at(ends.second).emplace_back(std::make_pair(ends.first, id));

	this->links_id.push_back(id);
	this->links.insert(std::make_pair(id, link(id, width, distance, ends)));
};


void city_builder::make_link(linkId id, std::pair<nodeId, nodeId> ends, double width) {
	auto nodes_vector = this->nodes;
	
	auto first = this->nodes.at(ends.first);
	auto second = this->nodes.at(ends.second);

	auto distance = sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));

	this->links_id.push_back(id);
	this->links.insert(std::make_pair(id, link(id, width, distance, ends)));

	this->connected_nodes_info.at(ends.first).emplace_back(std::make_pair(ends.second, id));
	this->connected_nodes_info.at(ends.second).emplace_back(std::make_pair(ends.first, id));
};