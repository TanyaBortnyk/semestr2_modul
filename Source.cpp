#include "WeatherUtils.h"

int main() {
    try {
        vector<WeatherRecord> data = readTSV("weather.tsv");

        map<string, pair<double, double>> result = computeMinMax(data);

        for (const auto& kv : result) {
            const string& city = kv.first;
            const pair<double, double>& temps = kv.second;

            cout << city << " -> Min: " << temps.first
                << ", Max: " << temps.second << endl;
        }

        saveToJSON("result.json", result);
    }
    catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "General error: " << e.what() << endl;
    }

    return 0;
}