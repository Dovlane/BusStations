#pragma once

#ifndef NOT_LOADED_COMMAND_H
#define NOT_LOADED_COMMAND_H

#include "Command.h"

class NotLoadedCommand : public Command {
public:
	NotLoadedCommand();
	Phase performAction(Traffic* traffic);
};

#endif
