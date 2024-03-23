#pragma once

#ifndef SHOW_STATION_TOUR_COMMAND_H
#define SHOW_STATION_TOUR_COMMAND_H

#include "Command.h"

class ShowTourCommand : public Command {
public:
	ShowTourCommand() = default;
	Phase performAction(Traffic* traffic);
};

#endif
