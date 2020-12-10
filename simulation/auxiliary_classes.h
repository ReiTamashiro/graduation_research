#pragma once

//auxiliary = 補助的、補助的な
#include <string>

#include <vector>
#include <deque>
#include <unordered_map>

#include <utility>
#include <memory>
#include <variant>

class agentId{
private:
	std::string item;
public:
	agentId() : item() {};
	agentId(const agentId &ai) : item(ai.item) {};
	agentId(const char *str) : item(str) {};
	agentId(const std::string &s) : item(s) {};

	std::string c_str() const {
		return this->item;
	}

	bool operator==(const agentId rhs) const {
		return this->item == rhs.item;
	}
};

class nodeId{
private:
	std::string item;
public:
	nodeId() : item() {};
	nodeId(const nodeId& ni) : item(ni.item) {};
	nodeId(const char* str) : item(str) {};
	nodeId(const std::string& s) : item(s) {};

	std::string c_str() const {
		return this->item;
	}

	bool operator==(const nodeId rhs) const {
		return this->item == rhs.item;
	}
};

class linkId{
private:
	std::string item;
public:
	linkId() : item() {};
	linkId(const linkId& li) : item(li.item) {};
	linkId(const char* str) : item(str) {};
	linkId(const std::string& s) : item(s) {};

	std::string c_str() const {
		return this->item;
	}

	bool operator==(const linkId rhs) const {
		return this->item == rhs.item;
	}
};

namespace std {
	template<>
	struct hash<agentId> {
		size_t operator()(const agentId& ai) const {
			return hash<string>()(ai.c_str());
		}
	};

	template<>
	struct hash<nodeId> {
		size_t operator()(const nodeId& ni) const {
			return hash<string>()(ni.c_str());
		}
	};

	template<>
	struct hash<linkId> {
		size_t operator()(const linkId& li) const {
			return hash<string>()(li.c_str());
		}
	};
}

using route = std::vector<nodeId>;

enum class state_agent { MOVE, ARRIVAL, FAILED };

struct id_had_agent {
	nodeId shelter_target;
	linkId link_current;
	nodeId node_previous;
	nodeId node_next;

	id_had_agent() {
		this->shelter_target = "";
		this->link_current = "";
		this->node_previous = "";
		this->node_next = "";
	};
	id_had_agent(nodeId shelter, linkId current, nodeId previous, nodeId next) : shelter_target(shelter), link_current(current), node_previous(previous), node_next(next) {};
	id_had_agent(const id_had_agent& x) : shelter_target(x.shelter_target), link_current(x.link_current), node_previous(x.node_previous), node_next(x.node_next){};
};

struct shelter {
private:
	unsigned int count;

public:
	const unsigned int capacity;

	shelter(unsigned int capacity) : capacity(capacity) {
		this->count = 0;
	};
	double rate() {
		if (count != 0) {
			return count / capacity;
		}
		return 0;
	};
	void increment() { this->count++; };
	unsigned int get_count() {
		return this->count;
	};
};

//左から感想・避難所混雑度・通行可否
using tweet = std::variant<std::string, std::vector<std::pair<nodeId, double>>,  std::vector<std::pair<linkId, bool>>>;
enum class tweet_type : unsigned int{ Impression=0 , TRAFFIC=1 , PASSABILITY=2};