#ifndef LAB7_DEBUGUI_H
#define LAB7_DEBUGUI_H

#include "CandyMachine.h"

class DebugUI {
protected:
    CandyMachine * candyMachine;
public:
    explicit DebugUI(CandyMachine * candyMachine) : candyMachine(candyMachine) { }

    virtual void startup() = 0;
    virtual void update() = 0;
};

#endif //LAB7_DEBUGUI_H
