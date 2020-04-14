#include "Agent.h"
#include <iostream>
#include <limits.h>
#include <math.h>
#include <iomanip>


Agent::Agent(string options) {
    setGain(0);
    setCurrStep(0   );
    vector<string> o = splitString(options);
    setCurrentTask(NULL);

    for (auto it = begin(o); it != end(o); ++it) {
        string element = *it;
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
    Task* task = getTask(taskName);
    task->setPerceivedUtility(value);


}

void Agent::decideAndAct() {
//    cout << "act" << endl;
}

string Agent::recharge() {
    string result = "state={";
    for (auto it = begin(taskHashMap); it != end(taskHashMap); ++it) {
        Task element = it->second;
        if (!element.isRealSeen())
            result += element.getName() + "=NA,";
        else
            result += element.getName() + "=" + truncateFloatPoint(element.getPerceivedUtility(), 2) + ",";

    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += truncateFloatPoint(getGain(), 2);
    return result;
}


void Agent::start() {
    string input;
    getline(cin, input);
    while (input.rfind("end", 0) != 0) {
        if (input.rfind("TIK", 0) == 0) {
            currStep++;
            decide();
        } else if (input.rfind("A u=", 0) == 0) act(stoi(input.substr(input.find('=') + 1, input.size())));
        else perceive(input);
        getline(cin, input);
    }

    cout << recharge();
}

double Agent::getMemoryWeight(string task) {
    double sum = 0;
    int visited = getTask(task)->getTimesSeen();
    for (int i = 1; i <= visited; i++)
        sum += pow(i, memoryFactor);
    return pow(visited, memoryFactor) / sum;
}

string Agent::truncateFloatPoint(double n, int _precision) {
    string number = to_string(round(n*100)/100);
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


Task* Agent::getTask(string task) {
    if(!taskHashMap.count(task))
        taskHashMap[task] = Task(task);
    return &taskHashMap[task];
}

Task* Agent::getCurrentTask() {
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
    Task* task = getTask(taskName);
    return task->getPerceivedUtility() * ((getSteps() - getCurrStep()) - getRestart() + task->getStepSeen());
}
