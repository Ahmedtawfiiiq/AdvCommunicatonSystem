#pragma once

template <class T>
class State
{
public:
    virtual void execute(T *) = 0; // pure virtual function
};
