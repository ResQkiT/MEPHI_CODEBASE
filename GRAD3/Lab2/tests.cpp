#include <iostream>
#include <functional>
#include <cassert>
#include "sorters/BinSearchInsertionSort.hpp"
#include "sorters/BubbleSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/ISorter.hpp"  
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"
#include "sorters/SelectionSorter.hpp"
#include "sorters/ShellSort.hpp"

#include <algorithm>

namespace tests
{
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

        for (auto i = arr.begin(); i != arr.end(); ++i)
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


    void run_all_tests(std::ostream &out){
        test_bubble_sorter(out);
        test_insertion_sorter(out);
        test_selection_sorter(out);
        test_merge_sorter(out);
        test_counting_sorter(out);
        test_bin_search_insertion_sort(out);
        test_shell_sort(out);
        test_quick_sorter(out);
        out << "All tests passed!" << std::endl;
    }
} // namespace tests


void run_tests(std::ostream &out)
{
    tests::run_all_tests(out);
}