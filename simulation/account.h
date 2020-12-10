#pragma once
#include "auxiliary_classes.h"
#include "auxiliary_function.h"


class account {
private:
	std::vector<std::pair<tweet, agentId>> Unread;
	
public:
	const agentId my_account;
	const std::vector<agentId> follow;
	const std::vector<agentId> follower;

	void add_unread_tweet(tweet message, agentId accountId);
	std::vector<std::pair<tweet, agentId>> read(void);
};