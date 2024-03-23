# BusStations

## Functional Specification
Implement a city transit network simulator in the C++ programming language. It is necessary to write a set of classes with corresponding methods, constructors, operators, and destructors for system realization.

## Loading Data about the City Transit Network
Implement the ability to load data about the city transit network from two text files.
The first text file contains information about stops, listing in each of its lines information about one stop in the format: stop_code stop_name, where the stop code is an integer and a unique identifier for the stop. After the name of the stop, an indicator of the stop's importance “[!]” may appear, denoting that the stop is located at an important city destination (e.g., 585 Tehnicki Fakulteti [!]).
The second text file contains information about city transit lines, listing in each of its lines information about one line and the stops through which the line passes in the format: line_mark stops where the line mark is textual and unique, and the stops include the codes of all stops through which the line passes in both directions (e.g., EKO1 654 585 583 190). The stops through which the line passes are listed in the order that the line passes through them.

## Displaying Information about the City Transit Network

Implement several operations that display information about the loaded city transit network.
Implement displaying information about a stop based on the given stop code. Information about the stop should include the stop code, stop name, marks of all lines that pass through the given stop, and codes of all important stops that are directly connected to the given stop in the format: code name [marks_of_all_lines] {! marks_of_important_stops !}, with lines sorted alphabetically and separated by spaces, and stops sorted numerically and separated by spaces (e.g., 585 Tehnicki Fakulteti [26 27 74 EKO1] {! 551 556 583 654 !}). Displaying information about a stop should be printed to a text file named stop_stop_code (e.g., stop_585.txt). Plan for the addition of new formats for displaying information about stops.
Implement displaying information about a line based on the given line mark. Information about the line should include the line mark, the starting and ending stop, and the codes and names of all stops through which the line passes. The display in the first row should list the line mark, then the names of the starting and ending stop in the format: line_mark starting_stop->ending_stop (e.g., EKO1 Vukov spomenik->Naselje Belvil). In each subsequent row, it is necessary to display the code, name, and possible importance indicator of the stops through which the line passes in the order that the line passes through them. Displaying information about lines should be printed to a text file named line_line_mark (e.g., line_27.txt). Plan for the addition of new formats for displaying information about lines.

## Simulation of Movement through the City Transit Network
Implement a simulation of movement through the city transit network. The simulation should, based on the selected starting and ending stop, generate a route between them. The result of the simulation is an output text file named path_start_end.txt, where start and end are the codes of the stops between which the route is generated (e.g., path_363_584.txt). The output file consists of pairs of lines, where the first line indicates the line to transfer to (see example), and the second line is a series of stop codes through which that line passes, including the stop where it is necessary to board the vehicle and the stop where it is necessary to leave the vehicle. The series of codes should be separated by spaces. The format of the output file is given in the example below. The output file contains 2*N rows, where N is the number of lines that need to be used on the route.
Plan three strategies for finding a route (the first strategy must be implemented, while the second and third strategies need to be implemented for the maximum number of points). The first strategy seeks any route between the starting and ending stop. The second strategy seeks the route with the fewest transfers needed between the starting and ending stop. The third strategy seeks a route that passes through all the important stops in the city transit network.

Example:
path_363_584.txt
->16 363 298 360 
16->EKO1
360 703 534 582 584

## Interaction with the User
Implement an interactive system with which the user can interact. The user interacts with the system by selecting one of the possible options that the system offers at that moment. Depending on the chosen option and its parameters, the program performs the corresponding operation and prints an output message or an error message. The error message should be as detailed as possible so that the user can easily resolve it. All parameters needed to perform an operation (input file name, line mark, etc.) should be requested from the user. An example of the interaction with the system is given below:

*Welcome to the city transit network simulator. Please choose an option:*  <br />
*1. Loading data about the city transit network*  <br />
*2. End of work*  <br />
 *1*  <br />
*Please enter the path to the file with stops or press ENTER to load the default file (inputs/stops.txt):*  <br /><br />
 *(enter)*  <br />
*The default file with stops has been loaded.*  <br />
*Please enter the path to the file with city transit lines or press ENTER to load the default file (inputs/lines.txt):*  <br />
 *inputs/new_lines.txt*  <br />
*The city transit network has been successfully loaded. Please choose an option:*  <br />
*1.  Display information about the stop*  <br />
*2.  Display information about the city transit line*  <br />
*3.  Finding a route between two stops*  <br />
*4.  End of work*  <br />
 *2*  <br />
*Please enter the line number whose information you want to display.*  <br />
 *EKO1*  <br />
*A file named line_EKO1.txt with basic information about line EKO1 has been generated.*  <br />
