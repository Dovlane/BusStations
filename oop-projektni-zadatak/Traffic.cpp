#include "Traffic.h"
#include "StringTrimmer.h"
#include "Exception.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <deque>
#include <tuple>
#include <utility>
#include <stack>
#include <unordered_set>
#include <set>


Traffic::Traffic() = default;

Traffic::~Traffic() = default;

void Traffic::loadStations(string& file_path) {
    ifstream input_stations(file_path);
    try {
        if (input_stations.is_open()) {
            while (input_stations.good()) {
                Station station = Station();
                input_stations >> station;
                if (station.isImportant())
                    important_stations.push_back(station.getPassword());
                stations.insert({ station.getPassword(), station });
            }
            input_stations.close();
        }
        else {
            throw IrregularPathException(file_path.c_str());
        }
    }
    catch (const IrregularPathException& e) {
        throw;
    }
}

void Traffic::loadLines(string& file_path) {
    ifstream input_lines(file_path);

    try {
        if (input_lines.is_open()) {
            while (input_lines.good()) {
                Line line = Line();
                input_lines >> line;
                lines.insert({ line.getName(), line });
                addEdgesOfLineInTraffic(line.getName());
            }
            input_lines.close();
        }
        else {
            throw IrregularPathException(file_path.c_str());
        }
    }
    catch (const IrregularPathException& e) {
        throw;
    }
}

void Traffic::addEdgesOfLineInTraffic(string& line_name) {
    Line& line = lines[line_name];
    size_t n = line.getStations().size();
    for (int i = 0; i < n - 1; i++) {
        int first_password = line.getStations()[i];
        int second_password = line.getStations()[i + 1];
        
        // traffic is bidirectional
        traffic[first_password][second_password].push_back(line_name);
        traffic[second_password][first_password].push_back(line_name);
    }
}

 void Traffic::printStations() {
    std::cout << "Stations: \n";
    for (const auto& station : stations) {
        std::cout << "\t" << station.second << endl;
    }
}

 void Traffic::printLines() {
    std::cout << "Lines: \n";
    for (const auto& line : lines) {
        std::cout << line.first << endl;
        
        for (int station : line.second.getStations()) {
            std::cout << "\t" << stations[station] << endl;
        }
    }
}

void Traffic::printTraffic() {
    std::cout << "Traffic: \n";
    for (const auto& pair_1 : traffic) {
        for (const auto& pair_2 : pair_1.second) {
            string lines = "";
            for (const auto& line_name : pair_2.second) {
                lines += line_name + " ";
            }
            std::cout << pair_1.first << " - " << pair_2.first << ":" << endl;
            std::cout << "\t" << lines << endl;
        }
    }
}

void Traffic::aboutLine(string line_name) {
    try {
        if (lines.count(line_name)) {
            const Line& line = lines[line_name];
            string file_name = "line_" + line_name + ".txt";
            ofstream file(file_name);
            if (file.is_open()) {
                int first_station = line.getStations()[0];
                int last_station = line.getStations()[line.getStations().size() - 1];
                string first_station_name = stations[first_station].getName();
                string last_station_name = stations[last_station].getName();
                file << line_name << " " << first_station_name << "->" << last_station_name << endl;
                for (int station : line.getStations()) {
                    file << stations[station] << endl;
                }
                file.close();
            }
            else {
                throw FileOpenException(file_name.c_str());
            }
        }
        else {
            throw NonExistingLineException(line_name.c_str());
        }
    }
    catch (const FileOpenException& e) {
        throw;
    }
    catch (const NonExistingLineException& e) {
        throw;
    }
}

void Traffic::aboutStation(int station_password) {
    try {
        if (!stations.count(station_password))
            throw NonExistingStationException(to_string(station_password).c_str());
        unordered_map<int, unordered_map<string, pair<int, string>>> path_map;
        unordered_map<int, unordered_map<string, int>> transfer_map;

        set<int> important_stations_without_transfers;
        set<string> line_set;

        for (const auto& st_ln : traffic[station_password]) {
            int next_station_password = st_ln.first;
            for (const string& line_name : st_ln.second) {
                if (find(important_stations.begin(), important_stations.end(), next_station_password) != important_stations.end()) {
                    important_stations_without_transfers.insert(next_station_password);
                }
                line_set.insert(line_name);
            }
        }

        Station& station = stations[station_password];

        string line_string = "[";
        for (const string& line : line_set) {
            line_string += line + " ";
        }
        StringTrimmer::trim(line_string);
        line_string += "]";

        string important_stations_string = "{! ";
        for (int station : important_stations_without_transfers) {
            important_stations_string += to_string(station) + " ";
        }
        important_stations_string += "!}";

        string file_name = "stop_" + to_string(station_password) + ".txt";
        ofstream file(file_name);
        if (file.is_open()) {
            file << station.getName() << " " << line_string << " " << important_stations_string << endl;
        }
        else {
            throw FileOpenException(file_name.c_str());
        }
        file.close();
    }
    catch (const NonExistingStationException& e) {
        throw;
    }
    catch (const FileOpenException& e) {
        throw;
    }
}

void Traffic::findRoute(int start_station, int end_station) {
    bool optimized = false;
    bool make_file = true;
    bool concat_to_another_path = false;
    try {
        findRoute(start_station, end_station, optimized, make_file, concat_to_another_path);
    }
    catch (const NonExistingStationException& e) {
        throw;
    }
    catch (const FileOpenException& e) {
        throw;
    }
    catch (const NoExistingRouteException& e) {
        throw;
    }
}

void Traffic::findRouteWithLeastTransfers(int start_station, int end_station) {
    bool optimized = true;
    bool make_file = true;
    bool concat_to_another_path = false;
    try {
        findRoute(start_station, end_station, optimized, make_file, concat_to_another_path);
    }
    catch (const NonExistingStationException& e) {
        throw;
    }
    catch (const FileOpenException& e) {
        throw;
    }
    catch (const NoExistingRouteException& e) {
        throw;
    }
}

void Traffic::findRouteAroundImportantStations() {
    // We are getting string_path by concatting paths between couples of important stations

    size_t n = important_stations.size();
    string string_path = "";
    for (int i = 0; i < n - 1; i++) {
        int first_password = important_stations[i];
        int second_password = important_stations[i + 1];
        try {
            string_path += findRoute(first_password, second_password, true, false, true);
        }
        catch (const FileOpenException& e) {
            throw;
        }
        catch (const NoExistingRouteException& e) {
            throw;
        }
    }
    int first_password = important_stations[n - 1];
    int second_password = important_stations[0];

    try {
        string_path += findRoute(first_password, second_password, true, false, false);
    }
    catch (const FileOpenException& e) {
        throw;
    }
    catch (const NoExistingRouteException& e) {
        throw;
    }

    // This path is still raw, since there is possible scenario where in route between consecutive three important stations same line is used.
    // In string_path it is manifested with strange transfers like "MINI->MINI". This is fixed by concatting the line before and line after
    // that strange transfer as in given example:
    // before:
    // 111 ([!]) 1221 1212 ([!])
    // MINI->MINI (this line is removed from string_path)
    // 1212 ([!]) 1221 111 ([!]) 1024 ([!])
    // after
    // 111 ([!]) 1221 1212 ([!]) 1221 111 ([!]) 1024 ([!])
   
    stringstream ss(string_path);
    vector<string> path_string_lines;
    while (!ss.eof()) {
        string curr;
        getline(ss, curr, '\n');
        path_string_lines.push_back(curr);
    }
    ss.clear();

    for (int i = 0; i < path_string_lines.size(); i++) {
        const string& curr = path_string_lines[i];
        size_t pos = curr.find("->");
        if (pos != string::npos && curr.size() == pos * 2 + 2) {
            const string line_1 = curr.substr(0, pos);
            const string line_2 = curr.substr(pos + 2, pos);
            if (line_1 == line_2) {
                string& prev = path_string_lines[i - 1];
                string& next = path_string_lines[i + 1];
                size_t space_pos_prev = prev.rfind(' ');
                prev = prev.substr(0, space_pos_prev);
                prev += " " + next;
                path_string_lines.erase(path_string_lines.begin() + i);
                path_string_lines.erase(path_string_lines.begin() + i);
                i--;
            }
        }
    }

    string_path = "";
    n = path_string_lines.size();
    for (int i = 0; i < n - 1; i++) {
        string_path += path_string_lines[i] + "\n";
    }
    string_path += path_string_lines[n - 1];


    
    // Write final concatted path to file
    try {
        string file_name = "around_important_stations.txt";
        ofstream file(file_name);
        if (file.is_open()) {
            file << string_path;
            file.close();
        }
        else {
            throw FileOpenException(file_name.c_str());
        }
    }
    catch (const FileOpenException& e) {
        throw;
    }
}

void Traffic::deleteStation(int station_to_delete) {
    if (!stations.count(station_to_delete))
        throw NonExistingStationException(to_string(station_to_delete).c_str());
    
    for (auto& pair : lines) {
        Line& line = pair.second;
        auto before_and_after = line.deleteStation(station_to_delete);
        int before_password = before_and_after.first;
        int after_password = before_and_after.second;
        if (before_password != -1) {
            traffic[before_password][station_to_delete].clear();
            traffic[station_to_delete][before_password].clear();
        }
        if (after_password != -1) {
            traffic[after_password][station_to_delete].clear();
            traffic[station_to_delete][after_password].clear();
        }
        if (before_password != -1 && after_password != -1) {
            traffic[after_password][before_password].push_back(line.getName());
            traffic[before_password][after_password].push_back(line.getName());
        }
    }

    stations.erase(station_to_delete);
}

string Traffic::findRoute(int start_station, int end_station, bool optimized, bool make_file, bool concat_to_another_path) {
    try {
        if (!stations.count(start_station))
            throw NonExistingStationException(to_string(start_station).c_str());
        if (!stations.count(end_station))
            throw NonExistingStationException(to_string(end_station).c_str());

        if (start_station == end_station) {
            string file_name = "path_" + to_string(start_station) + "_" + to_string(start_station) + ".txt";
            ofstream file(file_name);
            if (file.is_open()) {
                file << "Start is same as end" << endl;
                file.close();
            }
            else {
                throw FileOpenException(file_name.c_str());
            }
            return "";
        }

        unordered_map<int, unordered_map<string, pair<int, string>>> path_map;
        unordered_map<int, unordered_map<string, int>> transfer_map;

        for (const auto& station : stations) {
            for (const auto& line : lines) {
                transfer_map[station.first][line.first] = -1;
            }
        }

        deque<pair<int, string>> dq;
        for (const auto& st_ln : traffic[start_station]) {
            int next_station = st_ln.first;
            for (string line : st_ln.second) {
                transfer_map[start_station][line] = 0;
                path_map[start_station][line] = make_pair(-1, "");

                dq.push_front(make_pair(next_station, line));
                transfer_map[next_station][line] = transfer_map[start_station][line];
                path_map[next_station][line] = make_pair(start_station, line);
            }
        }

        while (!dq.empty()) {
            const auto& pair = dq.front();
            int curr_station = pair.first;
            string curr_line = pair.second;
            dq.pop_front();


            if (curr_station == end_station) {
                vector<vector<int>> station_path;
                vector<string> line_path;
                line_path.push_back(curr_line);
                station_path.push_back({ curr_station });
                while (true) {
                    auto& st_ln = path_map[curr_station][curr_line];
                    if (st_ln.first == -1)
                        break;
                    if (curr_line == st_ln.second) {
                        size_t curr_transfer = station_path.size();
                        station_path[curr_transfer - 1].push_back(st_ln.first);
                    }
                    else {
                        line_path.push_back(st_ln.second);
                        curr_line = st_ln.second;
                        station_path.push_back({ st_ln.first });
                    }
                    curr_station = st_ln.first;
                }

                while (!dq.empty()) {
                    dq.pop_front();
                }

                try {
                    return printPath(line_path, station_path, start_station, end_station, make_file, concat_to_another_path);
                }
                catch (const FileOpenException& e) {
                    throw;
                }
                station_path.clear();
                line_path.clear();
                break;
            }


            for (const auto& pair : traffic[curr_station]) {
                int next_station = pair.first;
                for (string line : pair.second) {
                    if (line == curr_line) {
                        bool should_add = false;
                        int transfer_for_next = transfer_map[next_station][curr_line];

                        if (transfer_map[next_station][curr_line] == -1 || transfer_map[next_station][curr_line] > transfer_map[curr_station][curr_line]) {
                            path_map[next_station][curr_line] = make_pair(curr_station, curr_line);
                            transfer_map[next_station][curr_line] = transfer_map[curr_station][curr_line];
                            should_add = true;
                        }
                        if (should_add) {
                            dq.push_front({ next_station, curr_line });
                        }
                    }
                    else {
                        bool should_add = false;
                        int transfer_for_next = transfer_map[next_station][curr_line];

                        if (transfer_map[next_station][line] == -1 || transfer_map[next_station][line] > transfer_map[curr_station][curr_line] + 1) {
                            path_map[curr_station][line] = make_pair(curr_station, curr_line);
                            transfer_map[curr_station][line] = transfer_map[curr_station][curr_line];
                            path_map[next_station][line] = make_pair(curr_station, line);
                            transfer_map[next_station][line] = transfer_map[curr_station][line] + 1;
                            should_add = true;
                        }
                        if (should_add) {
                            if (optimized)
                                dq.push_back({ next_station, line });
                            else
                                dq.push_front({ next_station, line });
                        }
                    }
                }
            }
        }
        string start_station_end_station = to_string(start_station) + " i " + to_string(end_station);
        throw NoExistingRouteException(start_station_end_station.c_str());
    }
    catch (const NonExistingStationException& e) {
        throw;
    }
    catch (const FileOpenException& e) {
        throw;
    }
    catch (const NoExistingRouteException& e) {
        throw;
    }
}

string Traffic::printPath(const vector<string>& line_path, const vector<vector<int>>& station_path, int start_station, int end_station, bool make_file, bool concat_to_another_path) {
    string path_string = "";

    size_t line_size = line_path.size();
    for (size_t i = line_size - 1; i > 0; i--) {
        path_string += "->" + line_path[i] + "\n";
        size_t station_line_size = station_path[i].size();
        for (size_t j = station_line_size - 1; j > 0; j--) {
            path_string += to_string(station_path[i][j]) + " ";
        }
        path_string += to_string(station_path[i][0]);
        path_string += "\n" + line_path[i];
    }
    path_string += "->" + line_path[0] + "\n";
    size_t station_line_size = station_path[0].size();
    for (size_t j = station_line_size - 1; j > 0; j--) {
        path_string += to_string(station_path[0][j]) + " ";
    }
    path_string += to_string(station_path[0][0]);
    
    if (concat_to_another_path) {
        path_string += "\n";
        path_string += line_path[0];
    }
    try {
        if (make_file) {
            string file_name = "path_" + to_string(start_station) + "_" + to_string(end_station) + ".txt";
            ofstream file(file_name);
            if (file.is_open()) {
                file << path_string;
                file.close();
                return path_string;
            }
            else
                throw FileOpenException(file_name.c_str());
        }
        else {
            return path_string;
        }
    }
    catch (const FileOpenException& e) {
        throw;
    }

}

