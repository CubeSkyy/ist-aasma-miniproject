//
// Created by CubeSky on 4/17/2020.
//

#ifndef EXERCISE_FLEXIBLEAGENT_H
#define EXERCISE_FLEXIBLEAGENT_H

#include <SimplexAlgorithm.h>
#include "Agent.h"

class FlexibleAgent : public Agent {
public:
    FlexibleAgent(const string &string);
    virtual void start();
    virtual string decide();
    void virtual act(int);
    virtual string recharge();

};


#endif //EXERCISE_FLEXIBLEAGENT_H
