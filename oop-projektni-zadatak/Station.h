#pragma once

#ifndef STATION_H
#define STATION_H

#include <string>
#include <unordered_map>

using namespace std;

class Station
{
private:
	// station name
	string name;
	// station password
	int password;
	// is important station or not
	bool important;
	// returns true if station's name ends with importance identifier
	static bool isImportant(const string& station_name);
public:
	Station();
	~Station();
	
	int getPassword();
	int getPassword() const;
	bool isImportant();
	bool isImportant() const;
	string& getName();
	const string& getName() const;

	friend istream& operator >> (istream&, Station&);
	friend ostream& operator << (ostream&, const Station&);
};

#endif // !STATION_H
