#pragma once
#include <chrono>
#include <functional>
#include <string>
#include <sstream>
#include <iomanip>

template <typename Func>
class ExecutionTimeMeasurer {
public:
        static double measure(Func func, int n) {
        double total_time = 0.0;

        for (int i = 0; i < n; ++i) {
            auto start_time = std::chrono::high_resolution_clock::now();
            func();
            auto end_time = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        }

        return (total_time) * 1e-6; 
    }
};
