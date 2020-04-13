//
// Created by CubeSky on 4/12/2020.
//

#ifndef EXERCISE_RATIONALEAGENT_H
#define EXERCISE_RATIONALEAGENT_H
#include "Agent.h"
#include <string>
using namespace std;
class RationaleAgent : public Agent {
public:
    RationaleAgent(string options);
    void virtual decideAndAct();
    virtual string decide();
    void virtual act(int);

};


#endif //EXERCISE_RATIONALEAGENT_H
