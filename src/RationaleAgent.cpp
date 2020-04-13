//
// Created by CubeSky on 4/12/2020.
//
#include <iostream>
#include "RationaleAgent.h"
#include <float.h>

RationaleAgent::RationaleAgent(string options) : Agent(options) {}

void RationaleAgent::decideAndAct() {

//    string input;
//    getline(cin, input);
//
//    int value = stoi(input.substr(input.find("=") + 1, input.size()));
//    perceivedUtility.find(min.first)->second = value;
//    gain += value;
}

string RationaleAgent::decide() {
    if (perceivedUtility.empty()) {
        cout << "Decide failed: No perceivedUtility were given.";
        return nullptr;
    }

    pair<string, double> max_pair = pair<string, double> ("null", FLT_MIN);
    for (auto it = begin(perceivedUtility); it != end(perceivedUtility); ++it) {
        pair<string, double> element = *it;
        if (element.second > max_pair.second) {
            max_pair = element;
        }
    }

    taskQueue.push(max_pair.first);
    return max_pair.first;
}


void RationaleAgent::act(int value) {
    string task = taskQueue.front();
    taskQueue.pop();

    double weight = getMemoryWeight();
    auto it = perceivedUtility.find(task);
    it->second = it->second * (1 - weight) + value * weight;

    it = realUtility.find(task);
    if (it != realUtility.end())
        it->second = it->second * (1 - weight) + value * weight;
    else
        realUtility.insert(pair<string, double>(task, (double) value));

    gain += value;
}


