#include "VectorUtils.h"

pair<int, int> findMinMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        throw EmptyContainer();
    }

    auto it = vec.begin();
    int min = *it;
    int max = *it;

    for (; it != vec.end(); ++it) {
        if (*it < min) min = *it;
        if (*it > max) max = *it;
    }

    return { min, max };
}