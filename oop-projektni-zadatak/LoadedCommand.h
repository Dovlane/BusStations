#pragma once

#ifndef LOADED_COMMAND_H
#define LOADED_COMMAND_H

#include "Command.h"

class LoadedCommand : public Command {
public:
	LoadedCommand();
	Phase performAction(Traffic* traffic);
};


#endif