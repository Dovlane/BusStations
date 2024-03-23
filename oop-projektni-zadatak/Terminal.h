#pragma once

#ifndef TERMINAL_H
#define TERMINAL_H
#include "Traffic.h"
#include "CommandManager.h"
#include <unordered_map>


using namespace std;

//enum Phase {
//	NOT_LOADED, LOADING, LOADED, STATION_INFO, LINE_INFO, PATH_BETWEEN_TWO_STATIONS, IMPORTANT_STATION_TOUR, EXIT, DELETE_STATION, TEST
//};

class Terminal {
private:
	CommandManager* commandManager;
	Traffic* traffic;
public:
	Terminal();
	~Terminal();
	int startTerminal();
};


#endif // !TERMINAL_H
