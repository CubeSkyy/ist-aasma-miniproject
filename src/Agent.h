#ifndef EXERCISE_AGENT_H
#define EXERCISE_AGENT_H
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

class Agent {

public:
    int steps;
    map<string, double> perceivedUtility;
    map<string, double> realUtility;
    queue<string> taskQueue;
    Agent(string);
    int gain;
    int currStep;
    float memoryFactor = 0;
    void perceive(string);
    void virtual decideAndAct();
    virtual string decide() = 0;
    void virtual act(int) = 0;
    string recharge();
    vector<string> splitString(string, string delimiter = " ");
    void start();
    double getMemoryWeight();

    string truncateFloatPoint(double number);
};


#endif //EXERCISE_AGENT_H
