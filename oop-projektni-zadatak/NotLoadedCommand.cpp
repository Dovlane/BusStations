#include "Exception.h"

#include "NotLoadedCommand.h"
#include <iostream>

NotLoadedCommand::NotLoadedCommand() {
	phase_map[0] = EXIT;
	phase_map[1] = LOADING;
}

Phase NotLoadedCommand::performAction(Traffic* traffic) {
    cout << "Please enter a command:\n";
    cout << "1. Loading data about the city transit network\n";
    cout << "0. End of operation\n";
    Phase phase = EXIT;
    while (1)
    {
        int command;
        cin >> command;
        if (changePhaseToCommandPhase(phase, command)) {
            return phase;
        }
        else {
            cout << "Such a command does not exist\n";
        }
    }
}