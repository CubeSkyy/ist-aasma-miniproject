#ifndef EXERCISE_AGENT_H
#define EXERCISE_AGENT_H

#include <string>
#include "Task.h"
#include <map>
#include <vector>
#include <quadmath.h>

using namespace std;

class Agent {

public:
    static map<string, int> tasksExecuting;

    map<string, Task> taskHashMap;

    explicit Agent(string);

    virtual void perceive(string);

    virtual string decide() = 0;

    void virtual act(int) = 0;
    void virtual act(string, int) = 0;

    virtual string recharge() = 0;

    vector<string> splitString(string, string delimiter = " ");

    virtual void start() = 0;

    __float128 getMemoryWeight(string);

    static string truncateFloatPoint(double number, int precision);

    virtual Task *getTask(string);

    __float128 getFullUtility(string taskName);

    virtual map<string, Task>* getTaskHashMap();

    static string getfloat128String(__float128 input);

    int restart;
    int steps;
    __float128 gain;
    int currStep;
    float memoryFactor = 0;
    Task *currentTask;
    int concurPenalty;

};


#endif //EXERCISE_AGENT_H
