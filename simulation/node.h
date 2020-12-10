#pragma once
#include "auxiliary_classes.h"
#include "auxiliary_function.h"

struct node{
	const nodeId id;
	const double x, y;

	node(nodeId id, double x, double y) : id(id), x(x), y(y) {};
};