
#include "HomogeneousAgent.h"


HomogeneousAgent::HomogeneousAgent(const string &options) : RationaleAgent(options) {}
map<string, Task> HomogeneousAgent::taskHashMap_;
map<string, Task> *HomogeneousAgent::getTaskHashMap() {
    return &taskHashMap_;
}
