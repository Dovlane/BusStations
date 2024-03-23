#pragma once

#ifndef STATION_COMMAND_H
#define STATION_COMMAND_H

#include "Command.h"

class ShowStationCommand : public Command {
public:
	ShowStationCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif