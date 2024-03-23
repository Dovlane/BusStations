#include "Exception.h"
#include "ShowLineCommand.h"
#include <iostream>

Phase ShowLineCommand::performAction(Traffic* traffic) {
    cout << "Please, enter the line number whose information you want to display.\n";
    while (true) {
        string line;
        cin >> line;
        try {
            (*traffic).aboutLine(line);
            cout << "A file named line_" + line + ".txt with basic information about the line " << line << " has been generated" << endl;
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