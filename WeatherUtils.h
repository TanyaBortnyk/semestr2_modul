#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

struct WeatherRecord {
    string date;
    string city;
    double temperature;
};

// перевірка температури
inline void checkTemperature(double temp) {
    if (temp <= -100 || temp >= 100) {
        throw out_of_range("Anomalous temperature detected!");
    }
}

// зчитування TSV
inline vector<WeatherRecord> readTSV(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("File not found");
    }

    vector<WeatherRecord> data;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string date, city, tempStr;

        getline(ss, date, '\t');
        getline(ss, city, '\t');
        getline(ss, tempStr, '\t');

        double temp = stod(tempStr);
        checkTemperature(temp);

        data.push_back({ date, city, temp });
    }

    return data;
}

// min/max по містах
inline map<string, pair<double, double>> computeMinMax(const vector<WeatherRecord>& data) {
    map<string, pair<double, double>> result;

    for (const auto& rec : data) {
        if (result.find(rec.city) == result.end()) {
            result[rec.city] = { rec.temperature, rec.temperature };
        }
        else {
            auto& p = result[rec.city];
            if (rec.temperature < p.first) p.first = rec.temperature;
            if (rec.temperature > p.second) p.second = rec.temperature;
        }
    }

    return result;
}

// запис у JSON
inline void saveToJSON(const string& filename, const map<string, pair<double, double>>& data) {
    json j;

    for (const auto& kv : data) {
        const string& city = kv.first;
        const pair<double, double>& temps = kv.second;
        j[city]["min"] = temps.first;
        j[city]["max"] = temps.second;
    }

    ofstream file(filename);
    file << j.dump(4);
}