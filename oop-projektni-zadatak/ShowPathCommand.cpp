#include "Exception.h"
#include "ShowPathCommand.h"
#include <iostream>

Phase ShowPathCommand::performAction(Traffic* traffic) {
    while (true) {
        cout << "Enter the codes of the stations between which you want to find a route:\n";
        int first_station;
        int second_station;
        cin >> first_station;
        cin >> second_station;
        try {
            (*traffic).findRoute(first_station, second_station);
            cout << "The file path_" + to_string(first_station) + "_" + to_string(second_station) + ".txt contains the route from station " + to_string(first_station) + " to station " + to_string(second_station) << endl;
            return LOADED;
        }
        catch (const FileOpenException& e) {
            cout << e.what() << endl;
        }
        catch (const NonExistingStationException& e) {
            cout << e.what() << endl;
        }
        catch (const NoExistingRouteException& e) {
            cout << e.what() << endl;
        }
    }
}