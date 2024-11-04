#include <iostream>
#include <chrono>
#include <functional>
#include <cassert>
#include <random>

#include "sorters/BinSearchInsertionSort.hpp"
#include "sorters/BubbleSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/ISorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"
#include "sorters/SelectionSorter.hpp"
#include "sorters/ShellSort.hpp"
#include "sorters/HeapSorter.hpp"
#include "sorters/TreeSorter.hpp"

#include <algorithm>

namespace tests
{
    int ELEMENTS_COUNT = 10000;

    int generate_random_number(int min, int max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    void measure_time(const std::string &func_name, std::function<void(void)> func, std::ostream &out)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        out << func_name << " took " << duration.count() << " seconds." << std::endl;
    }
    // Простые тесты для сортировщиков
    void test_bubble_sorter(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        BubbleSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "BubbleSorter test passed!" << std::endl;
    }

    void test_insertion_sorter(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        InsertionSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "InsertionSorter test passed!" << std::endl;
    }

    void test_selection_sorter(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        SelectionSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "SelectionSorter test passed!" << std::endl;
    }

    void test_merge_sorter(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        MergeSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "MergeSorter test passed!" << std::endl;
    }
    void test_counting_sorter(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        CountingSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); i++)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "CountingSorter test passed!" << std::endl;
    }

    void test_bin_search_insertion_sort(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        BinSearchInsertionSort<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "BinSearchInsertionSort test passed!" << std::endl;
    }

    void test_shell_sort(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        ShellSort<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "ShellSort test passed!" << std::endl;
    }

    void test_quick_sorter(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        QuickSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "QuickSorter test passed!" << std::endl;
    }

    void test_heap_sort(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        HeapSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "HeapSorter test passed!" << std::endl;
    }

    void test_tree_sort(std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        TreeSorter<int> sorter;
        sorter.sort(arr.begin(), arr.end(), std::less<int>());

        for (auto i = arr.begin(); i != arr.end(); ++i)
        {
            assert(*i == i - arr.begin() + 1);
        }
        out << "TreeSorter test passed!" << std::endl;
    }
    // Нагрузочные тесты
    void test_bubble_sorter_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        BubbleSorter<int> sorter;
        measure_time("BubbleSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_insertion_sorter_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        InsertionSorter<int> sorter;
        measure_time("InsertionSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_selection_sorter_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        SelectionSorter<int> sorter;
        measure_time("SelectionSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_merge_sorter_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        MergeSorter<int> sorter;
        measure_time("MergeSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_counting_sorter_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        CountingSorter<int> sorter;
        measure_time("CountingSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_bin_search_insertion_sort_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        BinSearchInsertionSort<int> sorter;
        measure_time("BinSearchInsertionSort", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_shell_sort_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        ShellSort<int> sorter;
        measure_time("ShellSort", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_quick_sorter_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        QuickSorter<int> sorter;
        measure_time("QuickSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_heap_sort_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        HeapSorter<int> sorter;
        measure_time("HeapSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void test_tree_sort_performance(std::ostream &out)
    {
        DynamicArray<int> arr;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generate_random_number(0, ELEMENTS_COUNT));
        }
        TreeSorter<int> sorter;
        measure_time("TreeSorter", [&]()
                     { sorter.sort(arr.begin(), arr.end()); }, out);
    }

    void run_all_tests(std::ostream &out)
    {
        test_bubble_sorter(out);
        test_insertion_sorter(out);
        test_selection_sorter(out);
        test_merge_sorter(out);
        test_counting_sorter(out);
        test_bin_search_insertion_sort(out);
        test_shell_sort(out);
        test_quick_sorter(out);
        test_heap_sort(out);
        test_tree_sort(out);
        out << "All tests passed!" << std::endl;

        out << "Starting Performance tests, " << ELEMENTS_COUNT << " int`s" << std::endl;
        test_bubble_sorter_performance(out);
        test_insertion_sorter_performance(out);
        test_selection_sorter_performance(out);
        test_merge_sorter_performance(out);
        test_counting_sorter_performance(out);
        test_bin_search_insertion_sort_performance(out);
        test_shell_sort_performance(out);
        test_quick_sorter_performance(out);
        test_heap_sort_performance(out);
        test_tree_sort_performance(out);
    }
} // namespace tests

void run_tests(std::ostream &out)
{
    tests::run_all_tests(out);
}