#include "systemStates.h"
#include "systemMachine.h"
#include "fileHandler.h"
#include "system.h"
#include <iostream>

#define MICROSECONDS 1000000

void EncoderState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().encoder();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::mapper]);
}

void MapperState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().mapper();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::scrambler]);
}

void ScramblerState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().scrambler();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::modulator]);
}

void ModulatorState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().modulator();
    FileHandler::getInstance().outFile(System::getInstance().sample);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::addCP]);
}

void AddCyclicPrefixState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().cyclicPrefixAdder();
    FileHandler::getInstance().outFile(System::getInstance().sample_cp);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::awgn]);
}

void AwgnState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().awgnChannel((uint8)stoi(FileHandler::getInstance().data[1]));
    FileHandler::getInstance().outFile(System::getInstance().sample_cp);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::removeCP]);
}

void RemoveCyclicPrefixState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().cyclicPrefixRemover();
    FileHandler::getInstance().outFile(System::getInstance().sample_cp);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::demodulator]);
}

void DemodulatorState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().demodulator();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::descrambler]);
}

void DescramblerState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().descrambler();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::demapper]);
}

void DemappperState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().demapper();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->changeState(systemMachinePtr->states[SystemMachine::decoder]);
}

void DecoderState::execute(SystemMachine *systemMachinePtr)
{
    System::getInstance().decoder();
    FileHandler::getInstance().outFile(System::getInstance().data);
    systemMachinePtr->done();
}
