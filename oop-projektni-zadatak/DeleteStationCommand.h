#pragma once

#ifndef DELETE_STATION_COMMAND_H
#define DELETE_STATION_COMMAND_H

#include "Command.h"

class DeleteStationCommand : public Command {
public:
	DeleteStationCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif
