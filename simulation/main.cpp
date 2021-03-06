//nlohmann-json
//json perser

//eigen3
//Matrix caluclation (header Only)

#include "stdafx.h"

#include "city.h"
#include "simulator.h"

#include <iostream>

void disp_info(std::vector<nodeId> nodes_id, std::unordered_map<nodeId, std::vector<std::pair<nodeId, linkId>>> connected_nodes) {
    for (auto name : nodes_id) {
        std::cout << name.c_str() << std::endl;
        for (auto info : connected_nodes.at(name)) {
            std::cout << "node_" << info.first.c_str() << "_for_" << info.second.c_str() << std::endl;
        }
        std::cout << "" << std::endl;
    }
}

void disp_info(city map) {
    for (auto name : map.nodes_id) {
        std::cout << name.c_str() << std::endl;
        for (auto info : map.connected_nodes_info.at(name)) {
            std::cout << "node_" << info.first.c_str() << "_for_" << info.second.c_str() << ":" << map.links.at(info.second.c_str()).distance << std::endl;
        }
        std::cout << "" << std::endl;
    }
}

int main(){
    std::vector<std::string> nil;
    linkId li = linkId("AAA");

    city_builder *foo = new city_builder();
    foo->make_node("A", 1, 2);
    foo->make_node("B", 3, 4);
    foo->make_node("C", 5, 6);
    foo->make_node("D", 5, 6);
    foo->make_node("E", 5, 6);

    foo->make_link("L_A", std::make_pair<std::string, std::string>("A", "B"), 6, 50);
    foo->make_link("L_B", std::make_pair<std::string, std::string>("B", "D"), 0.2, 70);
    foo->make_link("L_C", std::make_pair<std::string, std::string>("B", "E"), 5, 10);
    foo->make_link("L_D", std::make_pair<std::string, std::string>("E", "C"), 1, 20);
    foo->make_link("L_D", std::make_pair<std::string, std::string>("D", "C"), 1, 20);


    city map = city(foo);
//    disp_info(map.nodes_id, map.connected_nodes_info);
    disp_info(map);


    std::vector<std::shared_ptr<agent>> age;
    id_had_agent ids = id_had_agent("C", "L_A", "A", "B");
    std::vector<nodeId> one = { nodeId("B"), nodeId("C") };
    age.emplace_back(std::make_shared<agent>(agent(map, ids, 45.9, std::move(one))));
    age.emplace_back(std::make_shared<agent>(agent(map, ids, 5.0, std::move(one))));
    age.emplace_back(std::make_shared<agent>(agent(map, ids, 8.0, std::move(one))));
    age.emplace_back(std::make_shared<agent>(agent(map, ids, 9.0, std::move(one))));
    age.emplace_back(std::make_shared<agent>(agent(map, ids, 10.0, std::move(one))));

    for (int i = 0; i < 50; i++) {
        age.emplace_back(std::make_shared<agent>(agent(map, ids, 30.0, std::move(one))));
    }

    simulator sim = simulator(map, std::move(age));


    while (true) {
        unsigned int evacuating = 0;
        sim.startup();
        std::cout << sim.get_step() << ":node_" << sim.get_agents().at(0).get_identifications().node_previous.c_str() << ":position_" << sim.get_agents().at(0).get_position() << std::endl;

        for (auto x : sim.get_agents()) {
            if (x.get_state() == state_agent::MOVE) {
                evacuating++;
            }
        }

        if (evacuating == 0) {
            break;
        }
    }

    return 0;
}

