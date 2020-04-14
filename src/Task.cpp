//
// Created by CubeSky on 4/14/2020.
//

#include "Task.h"

#include <utility>

Task::Task(string name) : name(std::move(name)) {
    realSeen = false;
    timesSeen = 0;
    stepSeen = 1;
}

double Task::getPerceivedUtility() const {
    return perceivedUtility;
}

void Task::setPerceivedUtility(double _perceivedUtility) {
    Task::perceivedUtility = _perceivedUtility;
}

int Task::getTimesSeen() const {
    return timesSeen;
}

void Task::setTimesSeen(int _timesSeen) {
    Task::timesSeen = _timesSeen;
}

bool Task::isRealSeen() const {
    return realSeen;
}

void Task::setRealSeen(bool _realSeen) {
    Task::realSeen = _realSeen;
}

int Task::getStepSeen() const {
    return stepSeen;
}

void Task::setStepSeen(int _stepSeen) {
    Task::stepSeen = _stepSeen;
}

const string &Task::getName() const {
    return name;
}

Task::Task() {}

