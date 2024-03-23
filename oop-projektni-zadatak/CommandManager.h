#pragma once

#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "Command.h"
#include "LoadedCommand.h"
#include "NotLoadedCommand.h"
#include "TestCommand.h"
#include "DeleteStationCommand.h"
#include "ShowLineCommand.h"
#include "ShowStationCommand.h"
#include "LoadingCommand.h"
#include "ShowTourCommand.h"
#include "ShowPathCommand.h"
#include <unordered_map>

class CommandManager
{
private:
	Phase currentPhase;
	Command* currentCommand;
	LoadedCommand* loadedCommand;
	NotLoadedCommand* notLoadedCommand;
	TestCommand* testCommand;
	DeleteStationCommand* deleteStationCommand;
	ShowLineCommand* showLineCommand;
	ShowStationCommand* showStationCommand;
	ShowTourCommand* showTourCommand;
	ShowPathCommand* showPathCommand;
	LoadingCommand* loadingCommand;
	
	unordered_map<Phase, Command*> phaseCommandMap;
	bool endOfProgramme;


public:
	CommandManager();
	~CommandManager();
	void doCommand(Traffic* traffic);
	bool isEndOfProgramme();
};


#endif // COMMAND_MANAGER_H