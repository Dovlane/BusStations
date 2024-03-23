#pragma once

#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

#include "Command.h"

class TestCommand : public Command {
public:
	TestCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif
