#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <cassert>
#include "HashMap.hpp"

namespace test{
    void testInsertAndRetrieve() {
        HashMap<std::string, int> map;
        map["one"] = 1;
        map["two"] = 2;
        assert(map["one"] == 1);
        assert(map["two"] == 2);
    }

    void testOverwriteValue() {
        HashMap<int, std::string> map;
        map[1] = "initial";
        map[1] = "updated";
        assert(map[1] == "updated");
    }

    void testFindMethod() {
        HashMap<int, std::string> map;
        map[1] = "exists";
        assert(map.find(1).has_value());
        assert(!map.find(2).has_value());
    }

    void testEraseMethod() {
        HashMap<int, std::string> map;
        map[1] = "to be removed";
        map.erase(1);
        assert(map.size() == 0);
        assert(!map.find(1).has_value());
    }

    void testEmptyAndSize() {
        HashMap<int, std::string> map;
        assert(map.empty());
        map[1] = "not empty";
        assert(!map.empty());
        assert(map.size() == 1);
    }

    void testRehashing() {
        HashMap<int, int> map(0.75);
        for (int i = 0; i < 100; ++i) {
            map[i] = i * i;
        }
        assert(map.size() == 100);
        for (int i = 0; i < 100; ++i) {
            assert(map[i] == i * i);
        }

    }

    int all_test() {
        std::map<std::string, std::function<void()>> testMap = {
            {"Insert and Retrieve", testInsertAndRetrieve},
            {"Overwrite Value", testOverwriteValue},
            {"Find Method", testFindMethod},
            {"Erase Method", testEraseMethod},
            {"Empty and Size", testEmptyAndSize},
            {"Rehashing", testRehashing}
        };

        for (const auto& [testName, testFunc] : testMap) {
            std::cout << "Running test: " << testName << "...";
            testFunc();
            std::cout << "PASSED!\n";
        }

        std::cout << "All tests passed!\n";
        return 0;
    }
};

void run_test(){
    test::all_test();
}