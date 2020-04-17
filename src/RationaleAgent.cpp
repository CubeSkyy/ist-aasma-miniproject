#include <iostream>
#include "RationaleAgent.h"
#include <float.h>
#include <limits.h>
#include <cmath>

RationaleAgent::RationaleAgent(string options) : Agent(options) {}


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
            if(stoi(element.first.substr(1)) < stoi(max.name.substr(1))){
                    max = element.second;
                    maxUtil = currMaxUtil;
            }
        }else if (currMaxUtil > maxUtil) {
            max = element.second;
            maxUtil = currMaxUtil;
        }
    }

    if(currentTask != NULL && currentTask->name != max.name){
        currentTask->waitTime = 0;
    }
    currentTask = &_taskHashMap->at(max.name);
    if(currentTask->waitTime < restart){
        currentTask->waitTime++;
    }

    return max.name;
}


void RationaleAgent::act(int value) {
    Task* task = currentTask;
    task->stepSeen.push_back(currStep);
//    task->utilitySeen.push_back(value);
    __float128 weight = getMemoryWeight(task->name);
    __float128 one = strtoflt128 ("1.0", NULL);
    __float128 result;
    __float128 _value = strtoflt128 (to_string(value).c_str(), NULL);
    if(!task->realSeen){
        task->perceivedUtility = _value;
    }else{
        result = task->perceivedUtility * (one - weight) + _value * weight;
        task->perceivedUtility = result;
    }

    task->realSeen = true;
    gain += value;
}

void RationaleAgent::act(string taskName, int value) {
    Task* task = getTask(taskName);

    task->stepSeen.push_back(currStep);
    __float128 weight = getMemoryWeight(task->name);
    __float128 one = strtoflt128 ("1.0", NULL);
    __float128 result;
    __float128 _value = strtoflt128 (to_string(value).c_str(), NULL);
    if(!task->realSeen){
        task->perceivedUtility = _value;
    }else{
        result = task->perceivedUtility * (one - weight) + _value * weight;
        task->perceivedUtility = result;
    }

    task->realSeen = true;
    gain += _value;
}


void RationaleAgent::start() {
    string input;
    getline(cin, input);
    while (input.rfind("end", 0) != 0) {
        if (input.rfind("TIK", 0) == 0) {
            multiAgentFlag = true;
            decide();
            currStep++;
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
        if (!task.realSeen)
            result += taskName + "=NA,";
        else
            result += taskName + "=" + Agent::getfloat128String(task.perceivedUtility) + ",";

    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += truncateFloatPoint(gain, 2);
    result += "\n";
    return result;
}

map<string, Task> *RationaleAgent::getTaskHashMap() {
    return Agent::getTaskHashMap();
}
