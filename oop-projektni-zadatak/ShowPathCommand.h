#pragma once

#ifndef SHOW_PATH_COMMAND_H
#define SHOW_PATH_COMMAND_H

#include "Command.h"

class ShowPathCommand : public Command {
public:
	ShowPathCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif
