#include "systemMachine.h"
#include "systemStates.h"
#include "system.h"
#include "fileHandler.h"

SystemMachine::SystemMachine()
{
    states[encoder] = new EncoderState();
    states[mapper] = new MapperState();
    states[scrambler] = new ScramblerState();
    states[modulator] = new ModulatorState();
    states[addCP] = new AddCyclicPrefixState();
    states[awgn] = new AwgnState();
    states[removeCP] = new RemoveCyclicPrefixState();
    states[demodulator] = new DemodulatorState();
    states[descrambler] = new DescramblerState();
    states[demapper] = new DemappperState();
    states[decoder] = new DecoderState();
    System::getInstance().data21 = bitset<21>(FileHandler::getInstance().data[encoder]);
    System::getInstance().data.push_back(System::getInstance().data21.to_string());
    StateMachine<SystemMachine>::init(this, states[encoder]);
}

SystemMachine::~SystemMachine()
{
    delete states[encoder];
    delete states[mapper];
    delete states[scrambler];
    delete states[modulator];
    delete states[addCP];
    delete states[awgn];
    delete states[removeCP];
    delete states[demodulator];
    delete states[descrambler];
    delete states[demapper];
    delete states[decoder];
}

// execute current state
void SystemMachine::update()
{
    StateMachine<SystemMachine>::update();
}
