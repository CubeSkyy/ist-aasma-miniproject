#include "Agent.h"
#include <iostream>
#include <limits.h>
#include <math.h>
#include <iomanip>


Agent::Agent(string options) {
    setGain(0);
    setCurrStep(0);
    setCurrentTask(NULL);

    vector<string> o = splitString(options);
    for (const string &element : o) {
        string option = element.substr(0, element.find('='));
        string value = element.substr(element.find('=') + 1, element.size());
        if (option == "cycle")
            setSteps(stoi(value));
        else if (option == "memory-factor")
            setMemoryFactor(stof(value));
        else if (option == "restart")
            setRestart(stoi(value));
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
    task->perceivedUtility = value;
}

void Agent::decideAndAct() {
//    cout << "act" << endl;
}

__float128 Agent::getMemoryWeight(string task) {
    __float128 _i, _tmp, _result;
    __float128 _sum = strtoflt128 ("0.0", NULL);
    __float128 _memFactor = strtoflt128 (to_string(getMemoryFactor()).c_str(), NULL);
    for (int i: getTask(task)->stepSeen) {
        _i = strtoflt128 (to_string(i).c_str(), NULL);
        _sum += powq(_i, _memFactor);
    }
    _tmp = powq(strtoflt128(to_string(getCurrStep()).c_str(), NULL), _memFactor);
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

int Agent::getSteps() const {
    return steps;
}

void Agent::setSteps(int steps) {
    Agent::steps = steps;
}

double Agent::getGain() const {
    return gain;
}

void Agent::setGain(double gain) {
    Agent::gain = gain;
}

int Agent::getCurrStep() const {
    return currStep;
}

void Agent::setCurrStep(int currStep) {
    Agent::currStep = currStep;
}

float Agent::getMemoryFactor() const {
    return memoryFactor;
}

void Agent::setMemoryFactor(float memoryFactor) {
    Agent::memoryFactor = memoryFactor;
}


Task *Agent::getTask(string task) {
    map<string, Task> *_taskHashMap = getTaskHashMap();
    if (!_taskHashMap->count(task))
        _taskHashMap->emplace(task, Task(task));
    return &_taskHashMap->at(task);
}

Task *Agent::getCurrentTask() {
    return currentTask;
}

void Agent::setCurrentTask(Task *currentTask) {
    Agent::currentTask = currentTask;
}

int Agent::getRestart() const {
    return restart;
}

void Agent::setRestart(int restart) {
    Agent::restart = restart;
}

double Agent::getFullUtility(string taskName) {
    Task *task = getTask(taskName);
    return task->perceivedUtility * ((getSteps() - getCurrStep()) - getRestart() + task->getWaitTime());
}

map<string, Task> *Agent::getTaskHashMap() {
    return &taskHashMap;
}
