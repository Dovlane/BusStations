#include "Exception.h"
#include "TestCommand.h"
#include <iostream>

Phase TestCommand::performAction(Traffic* traffic) {
	cout << endl;
	(*traffic).printStations();
	cout << endl;
	(*traffic).printLines();
	cout << endl;
	(*traffic).printTraffic();
	return LOADED;
}