#pragma once
#include "city.h"

linkId city::search_next_link(const city* city, nodeId current, nodeId next) {
	for (auto x : city->connected_nodes_info.at(current)) {
		if (x.first == next) {
			return x.second;
		}
	}
	throw;
}