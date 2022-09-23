#pragma once

#include "state.h"

// abstract class for states for FSM (finite state machines)
// used to create our machines
template <class T>
class StateMachine
{
private:
    T *framePtr;               // pointer to our created machine
    State<T> *currentStatePtr; // pointer to current state
    bool firstRun = true;      // flag indicate start state
public:
    void init(T *, State<T> *);   // FSM initializer
    void changeState(State<T> *); // FSM state changer
    void update();                // FSM state executor
};

template <class T>
inline void StateMachine<T>::init(T *frameMachinePtr, State<T> *initialState)
{
    currentStatePtr = initialState;
    framePtr = frameMachinePtr;
}

template <class T>
inline void StateMachine<T>::changeState(State<T> *newState)
{
    currentStatePtr = newState; // change state pointer to new state
}

template <class T>
inline void StateMachine<T>::update()
{
    if (firstRun)
    {
        firstRun = false;
    }
    currentStatePtr->execute(framePtr);
}
