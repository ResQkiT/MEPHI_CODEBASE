#include <iostream>
#include <chrono>
#include <functional>
#include <cassert>
#include <random>
#include <memory>
#include <algorithm>
#include <map>
#include <string>

#include "sorters/ISorter.hpp"
#include "sorters/BinSearchInsertionSort.hpp"
#include "sorters/BubbleSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"
#include "sorters/SelectionSorter.hpp"
#include "sorters/ShellSort.hpp"
#include "sorters/HeapSorter.hpp"
#include "sorters/TreeSorter.hpp"
#include "DataGenerator.h"

namespace tests
{
    const int ELEMENTS_COUNT = 10000;

    void measure_time(const std::string &func_name, std::function<void(void)> func, std::ostream &out)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        out << func_name << " took " << duration.count() << " seconds." << std::endl;
    }

    static std::map<std::string, std::shared_ptr<ISorter<int>>> sorters = {
        {"BubbleSorter", std::make_shared<BubbleSorter<int>>()},
        {"InsertionSorter", std::make_shared<InsertionSorter<int>>()},
        {"SelectionSorter", std::make_shared<SelectionSorter<int>>()},
        {"MergeSorter", std::make_shared<MergeSorter<int>>()},
        {"CountingSorter", std::make_shared<CountingSorter<int>>()},
        {"BinSearchInsertionSort", std::make_shared<BinSearchInsertionSort<int>>()},
        {"ShellSort", std::make_shared<ShellSort<int>>()},
        {"QuickSorter", std::make_shared<QuickSorter<int>>()},
        {"HeapSorter", std::make_shared<HeapSorter<int>>()},
        {"TreeSorter", std::make_shared<TreeSorter<int>>()}
    };


    void test_sorter(const std::string & name, const std::shared_ptr<ISorter<int>> &sorter, std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        
        sorter->sort(arr.begin(), arr.end(), std::less<int>());

        for (size_t i = 0; i < arr.get_size(); ++i)
        {
            assert(arr[i] == i + 1);
        }

        out << name << " test passed!" << std::endl;
    }

    void performance_test_sorter(const std::string & name, const std::shared_ptr<ISorter<int>> &sorter, std::ostream &out)
    {
        DynamicArray<int> arr;
        DataGenerator generator;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generator.generate_random_number(0, ELEMENTS_COUNT));
        }

        measure_time(name, [&](){ sorter->sort(arr.begin(), arr.end()); }, out);
    }

    void run_all_tests(std::ostream &out)
    {
        out << "Running functional tests..." << std::endl;
        for (const auto &pair : sorters)
        {
            test_sorter(pair.first, pair.second, out);
        }
        out << "All functional tests passed!" << std::endl;

        out << "Running performance tests for " << ELEMENTS_COUNT << " elements..." << std::endl;
        for (const auto &pair : sorters)
        {
            performance_test_sorter(pair.first, pair.second, out);
        }
    }
}

void run_tests(std::ostream &out)
{
    tests::run_all_tests(out);
}
