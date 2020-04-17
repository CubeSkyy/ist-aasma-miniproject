#ifndef EXERCISE_TASK_H
#define EXERCISE_TASK_H

#include <string>
#include <vector>
#include <quadmath.h>

using namespace std;

class Task {
public:
    Task(string name);
    Task();
    __float128 perceivedUtility;
    vector<int> stepSeen;
    bool realSeen;
    int waitTime;
    string name;
    bool concurrent;
    bool operator== (const Task& task2) const
    {
        return name == task2.name;
    }

};

#endif //EXERCISE_TASK_H
