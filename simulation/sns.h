#pragma once

#include <unordered_map>
#include <memory>

#include "auxiliary_classes.h"
#include "auxiliary_function.h"

#include "account.h"


class sns {
	std::vector<agentId> accounts_id;
	std::unordered_map<agentId, std::shared_ptr<account>> accounts;
	std::unordered_map<agentId, double> effect;
	std::unordered_map<agentId, double> MoT;

};