//
// Created by CubeSky on 4/14/2020.
//

#ifndef EXERCISE_TASK_H
#define EXERCISE_TASK_H

#include <string>

using namespace std;

class Task {
public:

    double getPerceivedUtility() const;

    void setPerceivedUtility(double perceivedUtility);

    int getTimesSeen() const;

    void setTimesSeen(int timesSeen);

    bool isRealSeen() const;

    void setRealSeen(bool realSeen);

    int getStepSeen() const;

    void setStepSeen(int stepSeen);

private:
    double perceivedUtility;
    int timesSeen;
    bool realSeen;
    int stepSeen;
    string name;
public:
    Task(string name);

    Task();

public:
    const string &getName() const;
};


#endif //EXERCISE_TASK_H
