#include "Exception.h"
#include "LoadingCommand.h"
#include <iostream>

Phase LoadingCommand::performAction(Traffic* traffic) {
    cout << "Please enter the path to the file with stops or press ENTER to load the default file (inputs/stops.txt):\n";
    cin.get();
    while (1) {
        string file_path = "";
        char c;
        while (std::cin.get(c) && c != '\n') {
            file_path += c;
        }
        try {
            if (file_path == "") {
                file_path = "stops.txt";
                cout << "The default file with stops has been loaded.\n";
            }
            else
                cout << "The entered file with stops has been loaded.\n";
            (*traffic).loadStations(file_path);
            break;
        }
        catch (const IrregularPathException& e) {
            cout << e.what() << endl;
        }
    }

    cout << "Please enter the path to the city transit lines file or press ENTER to load the default file (inputs/lines.txt):\n";
    while (1) {
        string file_path = "";
        char c;
        while (std::cin.get(c) && c != '\n') {
            file_path += c;
        }
        try {
            if (file_path == "") {
                file_path = "lines.txt";
                cout << "The default file with lines has been loaded.\n";
            }
            else
                cout << "The entered file with lines has been loaded.\n";
            (*traffic).loadLines(file_path);
            break;
        }
        catch (const IrregularPathException& e) {
            cout << e.what() << endl;
        }
    }
    cout << "The city transit network has been successfully loaded.\n";

	return LOADED;
}