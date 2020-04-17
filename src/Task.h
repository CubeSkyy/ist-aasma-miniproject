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
    int tasksExecuting;

};

#endif //EXERCISE_TASK_H
