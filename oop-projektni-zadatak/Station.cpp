#include "Station.h"
#include "StringTrimmer.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;

/*
TO DO:

*/

Station::Station() = default;

Station::~Station() = default;

istream& operator >> (istream& is, Station& station) {
	is >> station.password;
	getline(is, station.name);
	StringTrimmer::trim(station.name);
	station.important = Station::isImportant(station.name);

	// removes importance identifier (in case it exists) from name after we identified it's importance
	string str_to_remove = " [!]";
	size_t pos = station.name.find(str_to_remove);
	if (pos != string::npos) {
		station.name.erase(pos, str_to_remove.length());
	}

	return is;
}

ostream& operator << (ostream& os, const Station& station) {
	string importance_identifier = ""; 
	if (station.important)
		importance_identifier = " [!]";
	return os << station.password << " " << station.name << importance_identifier;
}

bool Station::isImportant(const string& station_name) {
	size_t len = station_name.size();
	string spec_sign = station_name.substr(len - 3, 3);
	
	return spec_sign == "[!]";
}

bool Station::isImportant() {
	return important;
}

bool Station::isImportant() const {
	return important;
}

int Station::getPassword() {
	return password;
}

int Station::getPassword() const {
	return password;
}

string& Station::getName() {
	return name;
}

const string& Station::getName() const {
	return name;
}

