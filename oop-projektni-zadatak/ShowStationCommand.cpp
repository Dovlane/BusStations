#include "Exception.h"
#include "ShowStationCommand.h"
#include <iostream>

Phase ShowStationCommand::performAction(Traffic* traffic) {
    std::cout << "Please, enter the code of the station whose information you wish to display.\n";
    while (true) {
        int station;
        cin >> station;
        try {
            (*traffic).aboutStation(station);
            std::cout << "A file named stop_" + to_string(station) + ".txt with basic information about the station " << to_string(station) << " has been generated" << endl;
            return LOADED;
        }
        catch (const NonExistingLineException& e) {
            cout << e.what() << endl;
        }
        catch (const FileOpenException& e) {
            cout << e.what() << endl;
        }
    }
}