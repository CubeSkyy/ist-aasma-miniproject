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

    virtual int getCurrStep() const;

    virtual void setCurrStep(int currStep);

    float getMemoryFactor() const;

    void setMemoryFactor(float memoryFactor);

    explicit Agent(string);

    virtual void perceive(string);

    void virtual decideAndAct();

    virtual string decide() = 0;

    void virtual act(int) = 0;

    virtual string recharge() = 0;

    vector<string> splitString(string, string delimiter = " ");

    virtual void start() = 0;

    double getMemoryWeight(string);

    static string truncateFloatPoint(double number, int precision);

    virtual Task *getTask(string);

    virtual Task *getCurrentTask();

    virtual void setCurrentTask(Task *currentTask);

    int getRestart() const;

    void setRestart(int restart);

    double getFullUtility(string taskName);

    virtual map<string, Task>* getTaskHashMap();

//    double getMemoryTest(string _task);
private:
    int restart;
    int steps;
    double gain;
    int currStep;
    float memoryFactor = 0;
    Task *currentTask;


};


#endif //EXERCISE_AGENT_H
