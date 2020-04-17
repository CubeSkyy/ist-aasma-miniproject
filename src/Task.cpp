#include "Task.h"

#include <utility>

Task::Task(string name) : name(std::move(name)) {
    realSeen = false;
    waitTime = 0;
    concurrent = 0;
}
Task::Task() {}




