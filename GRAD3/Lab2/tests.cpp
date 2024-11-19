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


    void test_sorter(const std::string & name, std::shared_ptr<ISorter<int>> sorter, std::ostream &out)
    {
        DynamicArray<int> arr = {5, 4, 3, 2, 1};
        
        sorter->sort(arr.begin(), arr.end(), std::less<int>());

        for (size_t i = 0; i < arr.get_size(); ++i)
        {
            assert(arr[i] == i + 1);
        }

        out << name << " test passed!" << std::endl;
        
    }

    void performance_test_sorter(const std::string & name, std::shared_ptr<ISorter<int>> sorter, std::ostream &out)
    {
        DynamicArray<int> arr;
        DataGenerator generator;
        for (int i = 0; i < ELEMENTS_COUNT; i++)
        {
            arr.push_back(generator.generate_random_number(0, ELEMENTS_COUNT));
        }

        measure_time(name, [&](){ sorter->sort(arr.begin(), arr.end()); }, out);
    }


    struct User
    {
        std::string name;
        int age;

        bool operator==(const User &other) const
        {
            return name == other.name && age == other.age;
        }
    };


    void read_users_from_file(const std::string &file_path, DynamicArray<User> &users)
    {
        std::ifstream input_file(file_path);
        if (!input_file.is_open())
        {
            throw std::runtime_error("Could not open file for reading: " + file_path);
        }

        std::string line;
        while (std::getline(input_file, line))
        {
            std::istringstream iss(line);
            User user;

            std::string first_name, last_name;
            if (iss >> first_name >> last_name >> user.age)
            {
                user.name = first_name + " " + last_name;
                users.push_back(user);
            }
        }
    }


    void write_users_to_file(const std::string &file_path, DynamicArray<User> &users)
    {
        std::ofstream output_file(file_path);
        if (!output_file.is_open())
        {
            throw std::runtime_error("Could not open file for writing: " + file_path);
        }

        for (auto user : users)
        {
            output_file << user.name << " " << user.age << "\n";
        }
    }

    void test_user_sorting(std::ostream &out)
    {
        const std::string input_file = "../test_data_sort/user_input.txt";
        const std::string output_file = "../test_data_sort/user_output.txt";

        auto comp = [](const User &first, const User &second) {
                        return first.age < second.age;
                };

        DynamicArray<User> users;
        read_users_from_file(input_file, users);

        DynamicArray<User> custom_sorted_users(users);
    
        std::shared_ptr<ISorter<User>> sorter = std::make_shared<QuickSorter<User>>();
        
        sorter->sort(custom_sorted_users.begin(), custom_sorted_users.end(), comp);

        for(int i = 0; i < custom_sorted_users.get_size() - 1; i++)
        {
            assert(! comp(custom_sorted_users[i+1], custom_sorted_users[i])); //  Выполнено отношение частичной упорядоченности
        }
        
        write_users_to_file(output_file, custom_sorted_users);
        
        out << "User sorting test passed!" << std::endl;
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

        out << "Running user sorting tests..." << std::endl;
        test_user_sorting(out);
    }
}

void run_tests(std::ostream &out)
{
    tests::run_all_tests(out);
}
