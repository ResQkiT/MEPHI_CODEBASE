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
    std::string unique_name; 
    std::vector<std::function<bool(const T&)>> conditions;

public:

    Query() = delete;

    Query(const std::string& name) : unique_name(name) {}

    Query(const std::string& name, const std::vector<std::function<bool(const T&)>>& initial_conditions) 
        : unique_name(name), conditions(initial_conditions) {}

    Query(const std::string& name, std::initializer_list<std::function<bool(const T&)>> init_list) 
        : unique_name(name), conditions(init_list) {}

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

    bool operator==(const Query<T>& other) const {
        return unique_name == other.unique_name; 
    }

    bool operator!=(const Query<T>& other) const {
        return !(*this == other);
    }

    const std::string& get_unique_name() const {
        return unique_name;
    }


    struct Hash {
        std::size_t operator()(const Query<T>& query) const {
            return std::hash<std::string>()(query.unique_name);
        }
    };
};
