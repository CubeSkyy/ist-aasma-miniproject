#include <iostream>
#include <string>
#include "Agent.h"
#include "RationaleAgent.h"

using namespace std;

string getDecision(string input) {
    string decision = input.substr(input.find("decision=") + 9);
    decision = decision.substr(0, decision.find(' '));
    return decision;
}

vector<string> getAgentsNames(string input) {
    string decision = input.substr(input.find("agents=") + 8);
    string agentName;
    vector<string> result;
    for (char element : decision) {
        if (element == ']') {
            result.push_back(agentName);
            break;
        } else if (element == ',') {
            result.push_back(agentName);
            agentName = "";
        } else {
            agentName += element;
        }
    }
    return result;
}

string homogeneousRecharge(vector<string> agents, map<string, Task> taskHashMap, double gain) {
    string result = "state={";
    for (string agent : agents) {
        result += agent + "={";
        for (const auto &kv : taskHashMap) {
            string taskName = kv.first;
            Task task = kv.second;
            if (!task.isRealSeen())
                result += taskName + "=NA,";
            else
                result += taskName + "=" + Agent::truncateFloatPoint(task.getPerceivedUtility(), 2) + ",";

        }
        result.erase(result.size() - 1);
        result += "},";
    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += Agent::truncateFloatPoint(gain, 2);
    result += "\n";
    return result;
}

string heterogeneousRecharge(map<string, RationaleAgent *> agents) {
    string result = "state={";
    double gain = 0;
    for (const auto &kv2 : agents) {
        RationaleAgent *agent = kv2.second;
        result += kv2.first + "={";
        for (const auto &kv : *agent->getTaskHashMap()) {
            string taskName = kv.first;
            Task task = kv.second;
            if (!task.isRealSeen())
                result += taskName + "=NA,";
            else
                result += taskName + "=" + Agent::truncateFloatPoint(task.getPerceivedUtility(), 2) + ",";

        }
        gain += agent->getGain();
        result.erase(result.size() - 1);
        result += "},";
    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += Agent::truncateFloatPoint(gain, 2);
    result += "\n";
    return result;
}


int main(int argc, char *argv[]) {
//    freopen("../tests/public/T15_input.txt", "r", stdin);

    string input;
    getline(cin, input);
    string decision = getDecision(input);
    if (decision == "rationale") {
        RationaleAgent agent(input);
        agent.start();
        cout << agent.recharge();
    } else if (decision == "homogeneous-society") {
        RationaleAgent agent(input);
        agent.start();
        cout << homogeneousRecharge(getAgentsNames(input), *agent.getTaskHashMap(), agent.getGain());
    } else if (decision == "heterogeneous-society") {
        vector<string> agentNameVector = getAgentsNames(input);
        map<string, RationaleAgent *> agents;
        for (string agent : agentNameVector) {
            agents.insert(pair<string, RationaleAgent *>(agent, new RationaleAgent(input)));
        }

        getline(cin, input);
        while (input.rfind("end", 0) != 0) {
//            double A1T0, A1T1, A1T2, A1T3, A1T4, A2T0, A2T1, A2T2, A2T3, A2T4;
//            int step1, step2;
//            string task1, task2;
//            if (agents.at("A1")->getTaskHashMap()->find("T0") == agents.at("A1")->getTaskHashMap()->end()) {
//                A1T0 = -1000000000;
//            } else {
//                A1T0 = agents.at("A1")->getTaskHashMap()->at("T0").getPerceivedUtility();
//            }
//            if (agents.at("A1")->getTaskHashMap()->find("T1") == agents.at("A1")->getTaskHashMap()->end()) {
//                A1T1 = -1000000000;
//            } else {
//                A1T1 = agents.at("A1")->getTaskHashMap()->at("T1").getPerceivedUtility();
//            }
//            if (agents.at("A1")->getTaskHashMap()->find("T2") == agents.at("A1")->getTaskHashMap()->end()) {
//                A1T2 = -1000000000;
//            } else {
//                A1T2 = agents.at("A1")->getTaskHashMap()->at("T2").getPerceivedUtility();
//            }
//            if (agents.at("A1")->getTaskHashMap()->find("T3") == agents.at("A1")->getTaskHashMap()->end()) {
//                A1T3 = -1000000000;
//            } else {
//                A1T3 = agents.at("A1")->getTaskHashMap()->at("T3").getPerceivedUtility();
//            }
//            if (agents.at("A1")->getTaskHashMap()->find("T4") == agents.at("A1")->getTaskHashMap()->end()) {
//                A1T4 = -1000000000;
//            } else {
//                A1T4 = agents.at("A1")->getTaskHashMap()->at("T4").getPerceivedUtility();
//            }
//            if (agents.at("A2")->getTaskHashMap()->find("T0") == agents.at("A2")->getTaskHashMap()->end()) {
//                A2T0 = -1000000000;
//            } else {
//                A2T0 = agents.at("A2")->getTaskHashMap()->at("T0").getPerceivedUtility();
//            }
//            if (agents.at("A2")->getTaskHashMap()->find("T1") == agents.at("A2")->getTaskHashMap()->end()) {
//                A2T1 = -1000000000;
//            } else {
//                A2T1 = agents.at("A2")->getTaskHashMap()->at("T1").getPerceivedUtility();
//            }
//            if (agents.at("A2")->getTaskHashMap()->find("T2") == agents.at("A2")->getTaskHashMap()->end()) {
//                A2T2 = -1000000000;
//            } else {
//                A2T2 = agents.at("A2")->getTaskHashMap()->at("T2").getPerceivedUtility();
//            }
//            if (agents.at("A2")->getTaskHashMap()->find("T3") == agents.at("A2")->getTaskHashMap()->end()) {
//                A2T3 = -1000000000;
//            } else {
//                A2T3 = agents.at("A2")->getTaskHashMap()->at("T3").getPerceivedUtility();
//            }
//            if (agents.at("A2")->getTaskHashMap()->find("T4") == agents.at("A2")->getTaskHashMap()->end()) {
//                A2T4 = -1000000000;
//            } else {
//                A2T4 = agents.at("A2")->getTaskHashMap()->at("T4").getPerceivedUtility();
//            }
//            if (agents.at("A1")->getCurrentTask() == NULL){
//                task1 = "null";
//            } else {
//                task1 = agents.at("A1")->getCurrentTask()->getName();
//            }
//            if (agents.at("A2")->getCurrentTask() == NULL){
//                task2 = "null";
//            } else {
//                task2 = agents.at("A2")->getCurrentTask()->getName();
//            }
//            step1 = agents.at("A1")->getCurrStep();
//            step2 = agents.at("A2")->getCurrStep();

            if (input.rfind("TIK", 0) == 0) {
                for (const auto &kv : agents) {
                    RationaleAgent *agent = kv.second;
                    agent->decide();
                    agent->setCurrStep(agent->getCurrStep() + 1);
                }
            } else if (input.rfind('A', 0) == 0) {
                string agentName = input.substr(input.find('A'));
                agentName = agentName.substr(0, agentName.find(' '));
                agents.at(agentName)->act(stoi(input.substr(input.find('=') + 1, input.size())));
            } else {
                for (const auto &kv : agents) {
                    RationaleAgent *agent = kv.second;
                    agent->perceive(input);
                }
            }
            getline(cin, input);
        }

        cout << heterogeneousRecharge(agents);
    }
    return 0;
}
