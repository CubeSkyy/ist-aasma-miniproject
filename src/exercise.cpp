#include <iostream>
#include <string>
#include "Agent.h"
#include "RationaleAgent.h"
#include "HomogeneousAgent.h"
#include <algorithm>
#include <cmath>
#include "AllPermutation.h"

using namespace std;

string getOption(string input, string option) {
    if (input.find(option + "=") == std::string::npos) {
        return "NULL";
    }
    string decision = input.substr(input.find(option + "=") + option.size() + 1);
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

string societyResult(map<string, Agent *> agents) {
    string result = "state={";
    double gain = 0;
    for (const auto &kv2 : agents) {
        Agent *agent = kv2.second;
        result += kv2.first + "={";
        for (const auto &kv : *agent->getTaskHashMap()) {
            string taskName = kv.first;
            Task task = kv.second;
            if (!task.realSeen)
                result += taskName + "=NA,";
            else
                result += taskName + "=" + Agent::getfloat128String(task.perceivedUtility) + ",";

        }
        gain += agent->gain;
        result.erase(result.size() - 1);
        result += "},";
    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += Agent::truncateFloatPoint(gain, 2);
    result += "\n";
    return result;
}


// C++ implementation
#include <bits/stdc++.h>


vector<vector<Task>> findPermutations(map<string, Task> *taskMap, int n_agents) {
    Task tasks[taskMap->size()];
    int i = 0;
    for (auto &it : *taskMap) {
        tasks[i++] = it.second;
    }
    int len = sizeof(tasks) / sizeof(tasks[0]);
    int L = n_agents;

    int size = (int) pow(len, L);
    vector<vector<Task>> result(size, vector<Task>(L, Task()));

    for (int i = 0; i < size; i++) {
        vector<Task> res;
        int k = i;
        for (int j = 0; j < L; j++) {
            res.push_back(tasks[k % len]);
            k /= len;
        }
        result.at(i) = res;
    }
    return result;
}


vector<Task> getMaxCombination(vector<Agent *> agents) {
    map<string, Task> *taskMap = agents.front()->getTaskHashMap();
    vector<vector<Task>> result = findPermutations(taskMap, agents.size());
    vector<Task> max;
    double maxUtil = FLT_MIN;
    for (vector<Task> comb : result) {
        double util = 0;
        for (int i = 0; i < comb.size(); i++) {
            util += agents[i]->getFullUtility(comb[i].name);
            Agent::tasksExecuting[comb[i].name]++;
        }
        if (util > maxUtil) {
            max = comb;
            maxUtil = util;
        }
        Agent::tasksExecuting.clear();

    }
    sort(max.begin(), max.end(), [](const Task &lhs, const Task &rhs) //TODO: Change to Task
    {
        return lhs.name < rhs.name;
    });
    return max;
}


int main(int argc, char *argv[]) {
    freopen("../tests/public/T18_input.txt", "r", stdin);

    string input;
    getline(cin, input);
    string decision = getOption(input, "decision");
    string _penalty = getOption(input, "concurrency-penalty");
    int penalty;
    if (_penalty == "NULL") {
        penalty = 0;
    } else {
        penalty = stoi(_penalty);
    }
    if (decision == "rationale") {
        RationaleAgent agent(input);
        agent.start();
        cout << agent.recharge();
    } else if (decision == "homogeneous-society") {
        if (penalty != 0) {
            vector<string> agentNameVector = getAgentsNames(input);
            vector<Agent *> agentVector;
            map<string, Agent *> agents;
            for (string agent : agentNameVector) {
                Agent *a = new HomogeneousAgent(input);
                agents.insert(pair<string, Agent *>(agent, a));
                agentVector.push_back(a);
            }
            Agent *randomAgent = agents.begin()->second;
            getline(cin, input);
            vector<Task> maxComb;
            while (input.rfind("end", 0) != 0) {
                if (input.rfind("TIK", 0) == 0) {
                    maxComb = getMaxCombination(agentVector);
                } else if (input.rfind('A', 0) == 0) {
                    string agentName = input.substr(input.find('A'));
                    agentName = agentName.substr(0, agentName.find(' '));
                    int index = distance(agentNameVector.begin(),
                                         find(agentNameVector.begin(), agentNameVector.end(), agentName));
                    agents.at(agentName)->act(maxComb[index].name,
                                              stoi(input.substr(input.find('=') + 1, input.size())));
                } else {
                    randomAgent->perceive(input);
                }
                getline(cin, input);
            }
            cout << societyResult(agents);
        } else {
            vector<string> agentNameVector = getAgentsNames(input);
            vector<Agent *> agentVector;
            map<string, Agent *> agents;
            for (string agent : agentNameVector) {
                Agent *a = new HomogeneousAgent(input);
                agents.insert(pair<string, Agent *>(agent, a));
                agentVector.push_back(a);
            }
            Agent *randomAgent = agents.begin()->second;
            getline(cin, input);
            while (input.rfind("end", 0) != 0) {
                if (input.rfind("TIK", 0) == 0) {
                    for (const auto &kv : agents) {
                        Agent *agent = kv.second;
                        agent->decide();
                        agent->currStep++;
                    }
                } else if (input.rfind('A', 0) == 0) {
                    string agentName = input.substr(input.find('A'));
                    agentName = agentName.substr(0, agentName.find(' '));
                    agents.at(agentName)->act(stoi(input.substr(input.find('=') + 1, input.size())));
                } else {
                    randomAgent->perceive(input);
                }
                getline(cin, input);
            }
            cout << societyResult(agents);
        }
    } else if (decision == "heterogeneous-society") {
        if (penalty != 0) {
            vector<string> agentNameVector = getAgentsNames(input);
            vector<Agent *> agentVector;
            map<string, Agent *> agents;
            for (string agent : agentNameVector) {
                Agent *a = new RationaleAgent(input);
                agents.insert(pair<string, Agent *>(agent, a));
                agentVector.push_back(a);
            }
            Agent *randomAgent = agents.begin()->second;
            getline(cin, input);
            vector<Task> maxComb;
            while (input.rfind("end", 0) != 0) {
                if (input.rfind("TIK", 0) == 0) {
                    maxComb = getMaxCombination(agentVector);
                } else if (input.rfind('A', 0) == 0) {
                    string agentName = input.substr(input.find('A'));
                    agentName = agentName.substr(0, agentName.find(' '));
                    int index = distance(agentNameVector.begin(),
                                         find(agentNameVector.begin(), agentNameVector.end(), agentName));
                    agents.at(agentName)->act(maxComb[index].name,
                                              stoi(input.substr(input.find('=') + 1, input.size())));
                } else {
                    for (const auto &kv : agents) {
                        Agent *agent = kv.second;
                        agent->perceive(input);
                    }
                }
                getline(cin, input);
            }
            cout << societyResult(agents);
        }else{

            vector<string> agentNameVector = getAgentsNames(input);
            map<string, Agent *> agents;
            for (string agent : agentNameVector) {
                agents.insert(pair<string, Agent *>(agent, new RationaleAgent(input)));
            }

            getline(cin, input);
            while (input.rfind("end", 0) != 0) {
                if (input.rfind("TIK", 0) == 0) {
                    for (const auto &kv : agents) {
                        Agent *agent = kv.second;
                        agent->decide();
                        agent->currStep++;
                    }
                } else if (input.rfind('A', 0) == 0) {
                    string agentName = input.substr(input.find('A'));
                    agentName = agentName.substr(0, agentName.find(' '));
                    agents.at(agentName)->act(stoi(input.substr(input.find('=') + 1, input.size())));
                } else {
                    for (const auto &kv : agents) {
                        Agent *agent = kv.second;
                        agent->perceive(input);
                    }
                }
                getline(cin, input);
            }

            cout << societyResult(agents);
        }
    }
    return 0;
}
