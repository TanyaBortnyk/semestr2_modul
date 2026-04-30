#pragma once
#include <vector>
#include <exception>
#include <utility>
#include "iostream"
using namespace std;
class EmptyContainer : public exception {
public:
    const char* what() const noexcept override {
        return "EmptyContainer: vector is empty";
    }
};

pair<int, int> findMinMax(const vector<int>& vec);