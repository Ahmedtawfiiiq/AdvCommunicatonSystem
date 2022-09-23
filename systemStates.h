#pragma once
#include "state.h"

class EncoderState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class MapperState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class ScramblerState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class ModulatorState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class AddCyclicPrefixState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class AwgnState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class RemoveCyclicPrefixState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class DemodulatorState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class DescramblerState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class DemappperState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};

class DecoderState : public State<class SystemMachine>
{
public:
    void execute(SystemMachine *);
};
