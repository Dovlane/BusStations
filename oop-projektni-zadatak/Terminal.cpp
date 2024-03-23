#include "Terminal.h"
#include "Traffic.h"
#include "Exception.h"

#include <iostream>


Terminal::Terminal() {
	commandManager = new CommandManager();
	traffic = new Traffic();
}


Terminal::~Terminal() {
	delete commandManager;
	delete traffic;
}


int Terminal::startTerminal() {
    cout << "Welcome to the city transit network simulator." << endl;

    while (!commandManager->isEndOfProgramme()) {
        commandManager->doCommand(traffic);
    }

    return 0;
}
