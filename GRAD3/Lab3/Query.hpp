#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <numeric>

template <typename T>
class Query {
private:
    std::vector<std::function<bool(const T&)>> conditions;

public:
    Query() = default;

    Query(const std::vector<std::function<bool(const T&)>>& initial_conditions) 
        : conditions(initial_conditions) {}

    Query(std::initializer_list<std::function<bool(const T&)>> init_list) 
        : conditions(init_list) {}

    void add_condition(std::function<bool(const T&)> condition) {
        conditions.push_back(condition);
    }

    bool evaluate(const T& item) const {
        for (const auto& condition : conditions) {
            if (!condition(item)) {
                return false; 
            }
        }
        return true;
    }

    struct Hash {
        std::size_t operator()(const Query<T>& query) const {
            std::size_t seed = 0;
            for (const auto& condition : query.conditions) {
                seed ^= reinterpret_cast<std::size_t>(&condition) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
};
