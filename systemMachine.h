#pragma once
#include "stateMachine.h"

// our frame machine
class SystemMachine : public StateMachine<SystemMachine>
{
public:
    enum systemStates
    {
        encoder,
        mapper,
        scrambler,
        modulator,
        addCP,
        awgn,
        removeCP,
        demodulator,
        descrambler,
        demapper,
        decoder
    };
    State<SystemMachine> *states[11];
    bool doneFlag = false;

public:
    SystemMachine();
    ~SystemMachine();
    void update(); // call update function of parent class
    void done() { doneFlag = true; }
    bool isDone() { return doneFlag; }
};
