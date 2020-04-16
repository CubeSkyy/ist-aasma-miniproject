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
    bool isRealSeen() const;

    void setRealSeen(bool realSeen);

    int getWaitTime() const;

    void setWaitTime(int);

    const string &getName() const;

    vector<int> stepSeen;

private:
    bool realSeen;
    int waitTime;
    string name;
};


#endif //EXERCISE_TASK_H
