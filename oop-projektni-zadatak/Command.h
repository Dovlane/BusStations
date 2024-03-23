#pragma once

#ifndef COMMAND_H
#define COMMAND_H

#include "Traffic.h"

enum Phase {
	NOT_LOADED, LOADING, LOADED, STATION_INFO, LINE_INFO, PATH_BETWEEN_STATIONS, IMPORTANT_STATION_TOUR, EXIT, DELETE_STATION, TEST
};


class Command
{
protected:
	unordered_map<int, Phase> phase_map;
public:
	Command();
	virtual Phase performAction(Traffic* traffic) = 0;
	bool changePhaseToCommandPhase(Phase& phase, int command);
};
#endif