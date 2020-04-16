#include <iostream>
#include "RationaleAgent.h"
#include <float.h>
#include <limits.h>
#include <cmath>

RationaleAgent::RationaleAgent(string options) : Agent(options) {}

void RationaleAgent::decideAndAct() {

}

string RationaleAgent::decide() {
    map<string, Task>* _taskHashMap = getTaskHashMap();

    if (_taskHashMap->empty()) {
        cout << "Decide failed: No perceivedUtility were given.";
        return nullptr;
    }

    Task max = Task("NULL");
    auto maxUtil = (double) INT_MIN;
    double currMaxUtil;
    for (auto it = begin(*_taskHashMap); it != end(*_taskHashMap); ++it) {
        pair<string,Task> element = *it;
        currMaxUtil = getFullUtility(element.first);
        if(currMaxUtil == maxUtil){
            if(stoi(element.first.substr(1)) < stoi(max.getName().substr(1))){
                    max = element.second;
                    maxUtil = currMaxUtil;
            }
        }else if (currMaxUtil > maxUtil) {
            max = element.second;
            maxUtil = currMaxUtil;
        }
    }

    if(getCurrentTask() != NULL && getCurrentTask()->getName() != max.getName()){
        getCurrentTask()->setWaitTime(0);
    }
    setCurrentTask(&_taskHashMap->at(max.getName()));
    if(getCurrentTask()->getWaitTime() < getRestart()){
        getCurrentTask()->setWaitTime(getCurrentTask()->getWaitTime() + 1);
    }

    return max.getName();
}


void RationaleAgent::act(int value) {
    Task* task = getCurrentTask();
    task->stepSeen.push_back(getCurrStep());
//    task->utilitySeen.push_back(value);
    __float128 weight = getMemoryWeight(task->getName());
    __float128 one = strtoflt128 ("1.0", NULL);
    __float128 result;
    __float128 _value = strtoflt128 (to_string(value).c_str(), NULL);
    if(!task->isRealSeen()){
        task->perceivedUtility = _value;
    }else{
        result = task->perceivedUtility * (one - weight) + _value * weight;
        task->perceivedUtility = result;
    }

    task->setRealSeen(true);
    setGain(getGain() + value);
}

void RationaleAgent::start() {
    string input;
    getline(cin, input);
    while (input.rfind("end", 0) != 0) {
        if (input.rfind("TIK", 0) == 0) {
            multiAgentFlag = true;
            decide();
            setCurrStep(getCurrStep() + 1);
        } else if (input.rfind('A', 0) == 0) act(stoi(input.substr(input.find('=') + 1, input.size())));
        else perceive(input);
        getline(cin, input);
    }
}

string RationaleAgent::recharge() {
    string result = "state={";
    for (const auto& kv : taskHashMap) {
        string taskName = kv.first;
        Task task = kv.second;
        if (!task.isRealSeen())
            result += taskName + "=NA,";
        else
            result += taskName + "=" + Agent::getfloat128String(task.perceivedUtility) + ",";

    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += truncateFloatPoint(getGain(), 2);
    result += "\n";
    return result;
}

map<string, Task> *RationaleAgent::getTaskHashMap() {
    return Agent::getTaskHashMap();
}
