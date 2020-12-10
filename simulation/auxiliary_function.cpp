#pragma once
#include "auxiliary_function.h"

std::string get_unique_id(void) {
	static int counter = 0;
	return std::to_string(counter++);
}