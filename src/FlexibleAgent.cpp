//
// Created by CubeSky on 4/17/2020.
//
#include <iostream>
#include "FlexibleAgent.h"
#include <string>

FlexibleAgent::FlexibleAgent(const string &string) : Agent(string) {}


void FlexibleAgent::start() {
    string input;
    getline(cin, input);
    while (input.rfind("end", 0) != 0) {
        if (input.rfind("TIK", 0) == 0) {
            decide();
            currStep++;
        } else if (input.rfind('A', 0) == 0) {
            input = input.substr(input.find('=') + 2, input.size());
            if(input.find("{") != string::npos ){
                input.erase(input.size()-1);
                vector <string> tasks = splitString(input, ",");
                for(string s : tasks){
                    vector <string> element = splitString(s, "=");
                    string taskName = element[0];
                    int value = stoi(element[1]);
                    getTask(taskName)->perceivedUtility = getFullUtility(taskName) * getTask(taskName)->probability;
                }
            } else{
                act(stoi(input.substr(input.find('=') + 1, input.size())));

            }

        }
        else perceive(input);
        getline(cin, input);
    }
}



string FlexibleAgent::decide() {
    map<string, Task>* _taskHashMap = getTaskHashMap();

    if (_taskHashMap->empty()) {
        cout << "Decide failed: No perceivedUtility were given.";
        return nullptr;
    }
    vector<__float128> minUtil(_taskHashMap->size());
    vector<__float128> currUtil(_taskHashMap->size());

    for (auto it = begin(*_taskHashMap); it != end(*_taskHashMap); ++it) {
        Task element = it->second;
        minUtil.push_back(element.minValue);
        currUtil.push_back(element.perceivedUtility);
    }
    SimplexAlgorithm simplex = SimplexAlgorithm();
    simplex.generateData(minUtil, currUtil);
    vector<double> res = simplex.simplex();
    vector <Task*> v;

    for( auto it = _taskHashMap->begin(); it != _taskHashMap->end(); ++it ) {
        v.push_back(&it->second );
    }

    if(*max_element(begin(res), end(res)) != 1.0){

        string s_output = "{";
        for(int i = 0; i < res.size(); i++){
            if(res[i] != 0){
                s_output += v[i]->name + "=" + truncateFloatPoint(res[i], 2) + ",";
                v[i]->probability = res[i];
            }
        }
        s_output.erase(s_output.size() - 1);
        s_output += "}";
        cout << s_output;
    }else{
        int index = std::distance(res.begin(), std::max_element(res.begin(), res.end()));
        currentTask = v[index];
    }

    return "NULL";
}

string FlexibleAgent::recharge() {
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

void FlexibleAgent::act(int value) {
    Task* task = currentTask;
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
    gain += value;
}
