#include "Exception.h"
#include "DeleteStationCommand.h"
#include <iostream>

Phase DeleteStationCommand::performAction(Traffic* traffic)  {
    cout << "Enter the station you wish to delete:" << endl;

    while (true) {
        int station;
        cin >> station;
        try {
            (*traffic).deleteStation(station);
            cout << "Station " + to_string(station) << " has been deleted" << endl;
            return LOADED;
        }
        catch (const NonExistingStationException& e) {
            cout << e.what() << endl;
        }
    }

}