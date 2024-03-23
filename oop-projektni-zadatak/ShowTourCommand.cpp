#include "Exception.h"
#include "ShowTourCommand.h"
#include <iostream>

Phase ShowTourCommand::performAction(Traffic* traffic) {
    try {
        (*traffic).findRouteAroundImportantStations();
        cout << "In the file around_important_stations.txt is the route that passes through all important stations\n";
        return LOADED;
    }
    catch (const FileOpenException& e) {
        cout << e.what() << endl;
    }
    catch (const NoExistingRouteException& e) {
        cout << e.what() << endl;
    }
    return EXIT;
}