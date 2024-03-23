#pragma once

#ifndef LINE_H
#define LINE_H

#include <string>
#include <vector>
#include "Station.h"

using namespace std;

class Line {
private:
	// name of line
	string name;
	// stations through which line is going
	vector<int> stations;
public:
	Line();
	~Line();
	friend istream& operator >> (istream&, Line&);
	string& getName();
	const string& getName() const;
	void setName(string& new_name);
	pair<int, int> deleteStation(int station_password);
	vector<int>& getStations();
	const vector<int>& getStations() const;
};
#endif // !LINE_H
