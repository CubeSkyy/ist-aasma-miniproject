#include "Agent.h"
#include <iostream>
#include <limits.h>
#include <math.h>
#include <iomanip>


Agent::Agent(string options) {
    gain = 0;
    currStep = 0;
    vector<string> o = splitString(options);

    for (auto it = begin(o); it != end(o); ++it) {
        string element = *it;
        string option = element.substr(0, element.find('='));
        string value = element.substr(element.find('=') + 1, element.size());
        if (option == "cycle") {
            steps = stoi(value);
        } else if (option == "memory-factor") {
            memoryFactor = stof(value);
        }
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
    string task = inputVector[0];
    string utility = inputVector[1];
    int value = stoi(utility.substr(utility.find("=") + 1, utility.size()));

    double weight = getMemoryWeight();
    map<string, double>::iterator it = perceivedUtility.find(task);
    if (it != perceivedUtility.end())
        it->second = it->second * (1 - weight) + value * weight;
    else
        perceivedUtility.insert(pair<string, double>(inputVector[0], (double) value));


}

void Agent::decideAndAct() {
//    cout << "act" << endl;
}

string Agent::recharge() {
    string result = "state={";
    for (auto it = begin(perceivedUtility); it != end(perceivedUtility); ++it) {
        pair<string, double> element = *it;
        auto it2 = realUtility.find(element.first);
        if (it == realUtility.end())
            result += element.first + "=NA,";
        else
            result += element.first + "=" + truncateFloatPoint(it->second) + ",";

    }
    result.erase(result.size() - 1);
    result += "} gain=";
    result += to_string(gain);
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

    cout << recharge() << endl;
}

double Agent::getMemoryWeight() {
    double sum = 0;
    for (int i = 1; i <= currStep; i++)
        sum += pow(i, memoryFactor);
    return pow(currStep, memoryFactor) / sum;
}

string Agent::truncateFloatPoint(double n){
    string number = to_string(n);

    number.erase(number.find('.') + 2);

    return number;
}