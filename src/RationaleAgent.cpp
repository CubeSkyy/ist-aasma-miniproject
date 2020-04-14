//
// Created by CubeSky on 4/12/2020.
//
#include <iostream>
#include "RationaleAgent.h"
#include <float.h>
#include <limits.h>

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
    if (taskHashMap.empty()) {
        cout << "Decide failed: No perceivedUtility were given.";
        return nullptr;
    }

    Task max = Task("NULL");
    double maxUtil = (double) INT_MIN;
    double currMaxUtil;
    for (auto it = begin(taskHashMap); it != end(taskHashMap); ++it) {
        pair<string,Task> element = *it;
        currMaxUtil = getFullUtility(element.first);
        if (currMaxUtil > maxUtil) {
            max = element.second;
            maxUtil = currMaxUtil;
        }
    }
    taskHashMap[max.getName()].setStepSeen(taskHashMap[max.getName()].getStepSeen() + 1);

    if(getCurrentTask() != NULL && getCurrentTask()->getName() != max.getName())
        taskHashMap[getCurrentTask()->getName()].setStepSeen(1);
    setCurrentTask(&taskHashMap[max.getName()]);
    return max.getName();
}


void RationaleAgent::act(int value) {
    Task* task = getCurrentTask();
    task->setTimesSeen(task->getTimesSeen() + 1);
    double weight = getMemoryWeight(task->getName());
    if(!task->isRealSeen()){
        task->setPerceivedUtility((double) value);
    }else
        task->setPerceivedUtility(task->getPerceivedUtility() * (1 - weight) + value * weight);
    task->setStepSeen(task->getStepSeen() - 1);
    task->setRealSeen(true);
    setGain(getGain() + value);
}


