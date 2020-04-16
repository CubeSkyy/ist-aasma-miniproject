#include "Task.h"

#include <utility>

Task::Task(string name) : name(std::move(name)) {
    realSeen = false;
    waitTime = 0;
}

double Task::getPerceivedUtility() const {
    return perceivedUtility;
}

void Task::setPerceivedUtility(double _perceivedUtility) {
    Task::perceivedUtility = _perceivedUtility;
}

bool Task::isRealSeen() const {
    return realSeen;
}

void Task::setRealSeen(bool _realSeen) {
    Task::realSeen = _realSeen;
}

int Task::getWaitTime() const {
    return waitTime;
}

void Task::setWaitTime(int _waitTime) {
    Task::waitTime = _waitTime;
}

const string &Task::getName() const {
    return name;
}

Task::Task() {}


