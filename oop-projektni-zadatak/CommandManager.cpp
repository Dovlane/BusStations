#include "CommandManager.h"

CommandManager::CommandManager() {
	currentPhase = NOT_LOADED;
	endOfProgramme = false;
	currentCommand = nullptr;

	notLoadedCommand = new NotLoadedCommand();
	loadedCommand = new LoadedCommand();
	loadingCommand = new LoadingCommand();
	testCommand = new TestCommand();
	showStationCommand = new ShowStationCommand();
	showLineCommand = new ShowLineCommand();
	showTourCommand = new ShowTourCommand();
	showPathCommand = new ShowPathCommand();
	deleteStationCommand = new DeleteStationCommand();
	
	phaseCommandMap[NOT_LOADED] = notLoadedCommand;
	phaseCommandMap[LOADING] = loadingCommand;
	phaseCommandMap[LOADED] = loadedCommand;
	phaseCommandMap[TEST] = testCommand;
	phaseCommandMap[STATION_INFO] = showStationCommand;
	phaseCommandMap[LINE_INFO] = showLineCommand;
	phaseCommandMap[IMPORTANT_STATION_TOUR] = showTourCommand;
	phaseCommandMap[PATH_BETWEEN_STATIONS] = showPathCommand;
	phaseCommandMap[DELETE_STATION] = deleteStationCommand;
}

CommandManager::~CommandManager() {
	for (const auto &pair : phaseCommandMap) {
		delete phaseCommandMap[pair.first];
	}
	phaseCommandMap.clear();
}

void CommandManager::doCommand(Traffic* traffic) {
	if (currentPhase == EXIT) {
		endOfProgramme = true;
		return;
	}
	currentCommand = phaseCommandMap[currentPhase];
	currentPhase = currentCommand->performAction(traffic);
}

bool CommandManager::isEndOfProgramme() {
	return endOfProgramme;
}