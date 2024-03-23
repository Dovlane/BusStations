#include "Command.h"

Command::Command() {
	phase_map = {};
}

bool Command::changePhaseToCommandPhase(Phase& phase, int command) {
	if (phase_map.count(command)) {
		phase = phase_map[command];
		return true;
	}
	return false;
}