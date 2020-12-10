#include "account.h"

void account::add_unread_tweet(tweet message, agentId accountId) {
	this->Unread.push_back(std::make_pair(message, accountId));
}

std::vector<std::pair<tweet, agentId>> account::read() {
	auto res = this->Unread;
	this->Unread.clear();
	return res;
}