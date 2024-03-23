#pragma once

#ifndef TRAFFIC_H
#define TRAFFIC_H


#include "Station.h"
#include "Line.h"
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <vector>
#include <stack>

using namespace std;

class Traffic {
private:
	// keys for inner and outer map are station passwords (intigers), and vector<string> is a vector of all line names that lead from one station to another
	unordered_map<int, unordered_map<int, vector<string>>> traffic;
	
	// map of all lines in traffic
	unordered_map<string, Line> lines;
	
	// map of all stations in traffic
	unordered_map<int, Station> stations;
	
	// vector that keeps passwords of all important stations
	vector<int> important_stations;
	
	// as traffic lines are loading this method is called and map traffic is filled with edges between stations
	void addEdgesOfLineInTraffic(string& line_name);

	// Prints path determined by line_path and station_path. After first two parameters which are there to reconstruct the path between start and end station, parameters
	// after that are there for making file where reconstructed path is saved.
	string printPath(const vector<string>& line_path, const vector<vector<int>>& station_path, int start_station, int end_station, bool make_file, bool concat_to_another_path);
	
	// findRoute method returns path_string between start_station and end_station
	// optimized - determines if that path should be with as least transfers as possible
	// make_file - should this path_string be placed in file
	// concat_to_another_path - this parameter is there because of method findRouteAroundImportantStations(). Point of this is to concat paths between stations, and this method is in mentioned method called multiple times.
	string findRoute(int start_station, int end_station, bool optimized, bool make_file, bool concat_to_another_path);


public:
	Traffic();
	~Traffic();

	//Methods for loading stations and lines
	void loadStations(string& file_path);
	void loadLines(string& file_path);

	// These are test functions, that print content of maps lines, stations and traffic
	void printStations();
	void printLines();
	void printTraffic();

	// deletes station with given password
	void deleteStation(int station);

	// Returns info in proper file about line with name same as line_name
	void aboutLine(string line_name);

	// Returns info in proper file about station with password same as station_password
	void aboutStation(int station_password);
	
	// Returns route in proper file between start and end station. The route is find with something mostly similiar to DFS - not very wise strategy
	// this method basically calls method string findRoute(...), with parameters set with values: 
	// bool optimized = false
	// bool make_file = true
	// bool concat_to_another_path = false
	void findRoute(int start_station, int end_station);

	// Returns route in proper file between start and end station. The route is find with something mostly similiar to BFS - returns path with least transfers
	// this method basically calls method string findRoute(...), with parameters set with values: 
	// bool optimized = true
	// bool make_file = true
	// bool concat_to_another_path = false
	void findRouteWithLeastTransfers(int start_statoion, int end_station);

	// Returns route that goes through all stations that are marked as important. Route between each of important stations is found with strategy same as in method findRouteWithLeastTransfers()
	// this method basically calls multiple times method string findRoute(...), with parameters set with values: 
	// bool optimized = true
	// bool make_file = true (muliple paths are concating so we are not making file each time, it is going to be made once at the end, when all routes are concatted)
	// bool concat_to_another_path = true (except last call of string findRoute(...) method, there it is false, because we are closing file)
	void findRouteAroundImportantStations();
};

#endif // !TRAFFIC_H
