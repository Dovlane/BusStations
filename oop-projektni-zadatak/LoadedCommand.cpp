#include "Exception.h"
#include "LoadedCommand.h"
#include <iostream>

LoadedCommand::LoadedCommand() {
	phase_map[0] = EXIT;
	phase_map[1] = STATION_INFO;
	phase_map[2] = LINE_INFO;
	phase_map[3] = PATH_BETWEEN_STATIONS;
	phase_map[4] = IMPORTANT_STATION_TOUR;
	phase_map[5] = DELETE_STATION;
	phase_map[6] = TEST;
}

Phase LoadedCommand::performAction(Traffic* traffic) {
	cout << "Please, choose an option:\n";
	cout << "1. Display information about the stop\n";
	cout << "2. Display information about the city transit line\n";
	cout << "3. Finding a path between two stops\n";
	cout << "4. Tour of important stops\n";
	cout << "5. Deleting a station\n";
	cout << "6. Test function\n";
	cout << "0. End of operation\n";
	Phase phase = EXIT;
	while (true) {
		int command;
		cin >> command;
		if (changePhaseToCommandPhase(phase, command)) {
			return phase;
		}
		else {
			cout << "Such command does not exist\n";
		}
	}
}