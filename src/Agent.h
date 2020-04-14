#ifndef EXERCISE_AGENT_H
#define EXERCISE_AGENT_H

#include <string>
#include "Task.h"
#include <map>
#include <vector>

using namespace std;

class Agent {

public:
    map<string, Task> taskHashMap;

    int getSteps() const;

    void setSteps(int steps);

    double getGain() const;

    void setGain(double gain);

    int getCurrStep() const;

    void setCurrStep(int currStep);

    float getMemoryFactor() const;

    void setMemoryFactor(float memoryFactor);

    explicit Agent(string);

    void perceive(string);

    void virtual decideAndAct();

    virtual string decide() = 0;

    void virtual act(int) = 0;

    string recharge();

    vector<string> splitString(string, string delimiter = " ");

    void start();

    double getMemoryWeight(string);

    string truncateFloatPoint(double number, int precision);

    Task *getTask(string);

    Task *getCurrentTask();

    void setCurrentTask(Task *currentTask);

    int getRestart() const;

    void setRestart(int restart);

    double getFullUtility(string taskName);

private:
    int restart;
    int steps;
    double gain;
    int currStep;
    float memoryFactor = 0;
    Task *currentTask;

};


#endif //EXERCISE_AGENT_H
