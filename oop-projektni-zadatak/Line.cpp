#pragma once

#include "Line.h"
#include "Station.h"
#include <string>
#include <sstream>
#include "Exception.h"


using namespace std;

Line::Line() = default;

Line::~Line() = default;

istream& operator >> (istream& is, Line& line) {
    is >> line.name;
    string string_stations;
    getline(is, string_stations);
    stringstream ss(string_stations);

    while (ss.good()) {
        int station_password;
        ss >> station_password;
        line.stations.push_back(station_password);
    }

    return is;
}

vector<int>& Line::getStations() {
	return stations;
}

const vector<int>& Line::getStations() const {
    return stations;
}

const string& Line::getName() const {
    return name;
}

string& Line::getName() {
	return name;
}

void Line::setName(string& new_name) {
	name = new_name;
}

pair<int, int> Line::deleteStation(int station_password) {
    vector<int>::iterator it = find(stations.begin(), stations.end(), station_password);
    if (it != stations.end()) {
        vector<int>::iterator begin = stations.begin();
        vector<int>::iterator last = std::next(stations.end(), -1);
        int before_password = -1;
        int next_password = -1;
        if (it != begin) {
            auto before = std::next(it, -1);
            before_password = *before;
        }
        if (it != last) {
            auto next = std::next(it, 1);
            next_password = *next;
        }
        stations.erase(it);
        
        return make_pair(before_password, next_password);
    }
    return make_pair(-1, -1);
}
