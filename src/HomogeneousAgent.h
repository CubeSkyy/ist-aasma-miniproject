//
// Created by CubeSky on 4/16/2020.
//

#ifndef EXERCISE_HOMOGENEOUSAGENT_H
#define EXERCISE_HOMOGENEOUSAGENT_H

#include "RationaleAgent.h"
class HomogeneousAgent : public RationaleAgent {
public:
    static map<string, Task> taskHashMap_;
    HomogeneousAgent(const string &options);
    virtual map<string, Task>* getTaskHashMap();

};


#endif //EXERCISE_HOMOGENEOUSAGENT_H
