#include "Agent.h"
#include <iostream>
#include <limits.h>
#include <math.h>
#include <iomanip>

map<string, int> Agent::tasksExecuting;
Agent::Agent(string options) {
    gain = 0;
    currStep = 0;
    currentTask = NULL;
    vector<string> o = splitString(options);
    for (const string &element : o) {
        string option = element.substr(0, element.find('='));
        string value = element.substr(element.find('=') + 1, element.size());
        if (option == "cycle")
            steps =stoi(value);
        else if (option == "memory-factor")
            memoryFactor = stof(value);
        else if (option == "restart")
            restart = stoi(value);
        else if (option == "concurrentCost" || option == "concurrency-penalty")
            concurPenalty = stoi(value);
    }
}

vector<string> Agent::splitString(string s, string optionDelimiter) {
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = s.find(optionDelimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + optionDelimiter.length());
    }
    result.push_back(s);
    return result;
}

void Agent::perceive(string input) {
    vector<string> inputVector = splitString(input);
    string taskName = inputVector[0];
    string utility = inputVector[1];
    int value = stoi(utility.substr(utility.find("=") + 1, utility.size()));
    Task *task = getTask(taskName);
//    tasksExecuting[taskName] = 0;
    task->perceivedUtility = value;
}


__float128 Agent::getMemoryWeight(string task) {
    __float128 _i, _tmp, _result;
    __float128 _sum = strtoflt128 ("0.0", NULL);
    __float128 _memFactor = strtoflt128 (to_string(memoryFactor).c_str(), NULL);
    for (int i: getTask(task)->stepSeen) {
        _i = strtoflt128 (to_string(i).c_str(), NULL);
        _sum += powq(_i, _memFactor);
    }
    _tmp = powq(strtoflt128(to_string(currStep).c_str(), NULL), _memFactor);
    _result = _tmp / _sum;
    return _result;
}



string Agent::getfloat128String(__float128 input){
    int width = 50;
    char buf[128];
    quadmath_snprintf (buf, sizeof buf, "%*.2Qf", width, input);
    int count = 0;
    for (int i = 0; buf[i]; i++)
        if (buf[i] != ' ')
            buf[count++] = buf[i]; // here count is
    // incremented
    buf[count] = '\0';
    string result = string(buf);
    return result;
}


string Agent::truncateFloatPoint(double n, int _precision) {
    string number = to_string(round(n * 100) / 100);
    number.erase(number.find('.') + _precision + 1);

    return number;
}

Task *Agent::getTask(string task) {
    map<string, Task> *_taskHashMap = getTaskHashMap();
    if (!_taskHashMap->count(task))
        _taskHashMap->emplace(task, Task(task));
    return &_taskHashMap->at(task);
}


__float128 Agent::getFullUtility(string taskName) {
    Task *task = getTask(taskName);

    return (task->perceivedUtility - (concurPenalty * Agent::tasksExecuting[taskName])) * ((steps - currStep) - restart + task->waitTime);
}

map<string, Task> *Agent::getTaskHashMap() {
    return &taskHashMap;
}
