#pragma once

#include "link.h"

bool link::is_exists(nodeId id) {
	if (this->ends.first == id) {
		return true;
	}
	if (this->ends.second == id) {
		return true;
	}
	return false;
}