#pragma once

#ifndef SHOW_LINE_COMMAND_H
#define SHOW_LINE_COMMAND_H

#include "Command.h"

class ShowLineCommand : public Command {
public:
	ShowLineCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif
