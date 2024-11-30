#include <iostream>
#include <string>
#include <cstring>
#include "HashMap.hpp"
#include "test.h"
#include <cassert>
#include <unordered_map>
#include "DBAdapter.hpp"
#include "Query.hpp"
#include <iostream>
#include <chrono>
#include <functional>
#include "ExecutionTimeMeasurer.hpp"
#include "CachedDBAdapter.hpp"
#include <memory>

struct Record {
    int age;
    std::string name;
    Record(const std::string& line) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            age = std::stoi(line.substr(0, commaPos));
            name = line.substr(commaPos + 1);
        } else {
            throw std::invalid_argument("Invalid record format.");
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        run_test();
        return 0;
    }
    try {
        Query<Record> query("query");
        Query<Record>::Hash hash_fn;
        query.add_condition([](const Record& x) { return x.age < 19; });
        query.add_condition([](const Record& x) { return x.age > 0; });


        std::unique_ptr<DBAdapter<Record>> default_adapter = std::make_unique<DBAdapter<Record>>("../test_data/data.txt");

        auto measure_time1 = [&]() {
            
            auto matching_records = default_adapter->find(query);
            //std::cout << "Were found " << matching_records.size() << " records" << "\n"; 
            // for (const auto& record : matching_records) {
            //     std::cout << "AGE: " << record.age << ", Name: " << record.name << std::endl;
            // }
        };
        std::cout << "default time (5): " << ExecutionTimeMeasurer<decltype(measure_time1)>::measure(measure_time1, 5) << " seconds" << std::endl;


        std::unique_ptr<DBAdapter<Record>> cached_adapter = std::make_unique<CachedDBAdapter<Record>>("../test_data/data.txt", 10);

        auto measure_time2 = [&]() {
            
            auto matching_records = cached_adapter->find(query);
            //std::cout << "Were found " << matching_records.size() << " records" << "\n"; 
            // for (const auto& record : matching_records) {
            //     std::cout << "AGE: " << record.age << ", Name: " << record.name << std::endl;
            // }
        };
        std::cout << "cached time (5): " << ExecutionTimeMeasurer<decltype(measure_time2)>::measure(measure_time2, 5) << " seconds" << std::endl;

        std::size_t hash_value = hash_fn(query);
        std::cout << "Requested hash:"<< hash_value << "\n"; 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
    
}
