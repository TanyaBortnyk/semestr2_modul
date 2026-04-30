#include "VectorUtils.h"

using namespace std;

int main() {
    vector<int> vec;
    int x;

    cout << "Enter integers (Ctrl+Z / Ctrl+D to stop):\n";

    while (cin >> x) {
        vec.push_back(x);
    }

    try {
        auto result = findMinMax(vec);
        cout << "Min: " << result.first << endl;
        cout << "Max: " << result.second << endl;
    }
    catch (const EmptyContainer& e) {
        cout << e.what() << endl;
    }

    return 0;
}