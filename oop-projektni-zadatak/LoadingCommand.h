#pragma once

#ifndef LOADING_COMMAND_H
#define LOADING_COMMAND_H

#include "Command.h"

class LoadingCommand : public Command {
public:
	LoadingCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif
