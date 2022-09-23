#include "systemMachine.h"
#include "fileHandler.h"
#include <iostream>
int main()
{
    FileHandler::getInstance().inFile("input.txt");
    FileHandler::getInstance().openFile("output.txt");

    SystemMachine stateMachine;
    while (!stateMachine.isDone())
    {
        stateMachine.update();
    }

    FileHandler::getInstance().closeFile();

    return 0;
}
