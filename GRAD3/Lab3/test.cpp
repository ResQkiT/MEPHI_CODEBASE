#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <cassert>
#include <memory>
#include <iomanip> 
#include "HashMap.hpp"
#include "DBAdapter.hpp"
#include "CachedDBAdapter.hpp"
#include "ExecutionTimeMeasurer.hpp"
#include "Query.hpp"
#include "PriorityQueue.hpp"    

namespace test{
    class User {
    public:
        User() = default;
        User(int id, const std::string& name) : id(id), name(name) {}

        bool operator==(const User& other) const {
            return id == other.id && name == other.name;
        }

        bool operator!=(const User& other) const {
            return !(*this == other);
        }

        friend std::ostream& operator<<(std::ostream& os, const User& user) {
            os << "User{id: " << user.id << ", name: " << user.name << "}";
            return os;
        }
        struct Hash {
            size_t operator()(const User& user) const {
                return std::hash<std::string>{}(user.name);
            }
        };

    private:
        int id = 0;
        std::string name;
    };

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

    void testInsertAndRetrieveUser() {
        HashMap<User, std::string, User::Hash> map;

        User user1(1, "Alice");
        User user2(2, "Bob");

        map[user1] = "Engineer";
        map[user2] = "Doctor";

        assert(map[user1] == "Engineer");
        assert(map[user2] == "Doctor");
    }

    void testOverwriteUserValue() {
        HashMap<User, std::string, User::Hash> map;

        User user1(1, "Alice");
        map[user1] = "Engineer";
        map[user1] = "Manager";

        assert(map[user1] == "Manager");
    }

    void testFindUserMethod() {
        HashMap<User, std::string, User::Hash> map;
        
        User user1(1, "Alice");
        map[user1] = "Engineer";
        
        assert(map.find(user1).has_value());
        assert(!map.find(User(2, "Bob")).has_value());
    }

    void testEraseUserMethod() {
        HashMap<User, std::string, User::Hash> map;
        
        User user1(1, "Alice");
        map[user1] = "Engineer";
        
        map.erase(user1);
        
        assert(map.size() == 0);
        assert(!map.find(user1).has_value());
    }

    void testEmptyAndSizeUser() {
        HashMap<User, std::string, User::Hash> map;
        
        assert(map.empty());
        
        User user1(1, "Alice");
        map[user1] = "Engineer";
        
        assert(!map.empty());
        assert(map.size() == 1);
    }

    void testPriorityQueuePush() {
        PriorityQueue<int> pq;
        pq.push(10, 1);
        pq.push(20, 2);
        pq.push(5, 0);
        assert(pq.top() == 20);
    }

    void testPriorityQueuePop() {
        PriorityQueue<int> pq;
        pq.push(10, 1);
        pq.push(20, 2);
        pq.push(5, 0);
        pq.pop();
        assert(pq.top() == 10);
        pq.pop();
        assert(pq.top() == 5);
    }

    void testPriorityQueueTop() {
        PriorityQueue<int> pq;
        pq.push(10, 1);
        pq.push(20, 2);
        pq.push(5, 0);
        assert(pq.top() == 20);
        pq.pop();
        assert(pq.top() == 10);
    }

    void testPriorityQueueEmpty() {
        PriorityQueue<int> pq;
        assert(pq.empty());
        pq.push(10, 1);
        assert(!pq.empty());
        pq.pop();
        assert(pq.empty());
    }

    void testPriorityQueueSize() {
        PriorityQueue<int> pq;
        assert(pq.size() == 0);
        pq.push(10, 1);
        pq.push(20, 2);
        assert(pq.size() == 2);
        pq.pop();
        assert(pq.size() == 1);
    }

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
    

    void testReadAll() {
        DBAdapter<Record> dbAdapter("../test_data/small_data.txt");
        std::vector<Record> records = dbAdapter.readAll();
        assert(!records.empty());
    }

    void testReadNext() {
        DBAdapter<Record> dbAdapter("../test_data/small_data.txt");
        Record record = dbAdapter.readNext();
        assert(record.name != "");
    }

    void testFind() {
        DBAdapter<Record> dbAdapter("../test_data/small_data.txt");

        Query<Record> query("Age greater than 60");
        query.add_condition([](const Record& x) { return x.age > 60; });

        std::vector<Record> results = dbAdapter.find(query);
        for (const auto& record : results) {
            assert(record.age > 60);
        }
    }

    void testFindNoMatches() {
        DBAdapter<Record> dbAdapter("../test_data/small_data.txt");

        Query<Record> query("Age greater than 200");
        query.add_condition([](const Record& x) { return x.age > 200; });

        std::vector<Record> results = dbAdapter.find(query);
        assert(results.empty());
    }

    void run_performance_test(){
        std::cout << "\n";
        std::unique_ptr<DBAdapter<Record>> dbAdapter = std::make_unique<DBAdapter<Record>>("../test_data/small_data.txt");
        std::unique_ptr<CachedDBAdapter<Record>> cachedAdapter = std::make_unique<CachedDBAdapter<Record>>("../test_data/small_data.txt", 10);

        std::map<std::string, Query<Record>> queries = {
            {"Name starts with A", Query<Record>("Name starts with A", {[](const Record& x) { return x.name[0] == 'A'; }})},
            {"Age greater than 60", Query<Record>("Age greater than 60", {[](const Record& x) { return x.age > 60; }})},
            {"Age less than 19", Query<Record>("Age less than 19", {[](const Record& x) { return x.age < 19; }})},
            {"Age between 20 and 30", Query<Record>("Age between 20 and 30", {[](const Record& x) { return x.age >= 20 && x.age <= 30; }})}
        };

        std::cout << std::setw(30) << "Query" << std::setw(20) << "DBAdapter (s)" << std::setw(20) << "CachedDBAdapter (s)" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
        const int num_cycles = 10; 
        
        for (const auto& query : queries) {
            
            double total_dbAdapterTime = 0;
            double total_cachedAdapterTime = 0;

            for (int cycle = 0; cycle < num_cycles; ++cycle){
                auto lambda = [&]() {
                    dbAdapter->find(query.second);
                };
                auto lambda2 = [&]() {
                    cachedAdapter->find(query.second);
                };
                double dbAdapterTime = ExecutionTimeMeasurer<decltype(lambda)>::measure(lambda, 1);

                double cachedAdapterTime = ExecutionTimeMeasurer<decltype(lambda2)>::measure(lambda2, 1);

                total_dbAdapterTime += dbAdapterTime;
                total_cachedAdapterTime += cachedAdapterTime;
            }

            double avg_dbAdapterTime = total_dbAdapterTime / num_cycles;
            double avg_cachedAdapterTime = total_cachedAdapterTime / num_cycles;

            std::cout << std::setw(30) << query.first << std::setw(20) << avg_dbAdapterTime << std::setw(20) << avg_cachedAdapterTime << std::endl;
        };
    }

    int all_test() {
        std::map<std::string, std::function<void()>> testMap = {
            {"Insert and Retrieve", testInsertAndRetrieve},
            {"Overwrite Value", testOverwriteValue},
            {"Find Method", testFindMethod},
            {"Erase Method", testEraseMethod},
            {"Empty and Size", testEmptyAndSize},
            {"Rehashing", testRehashing},

            {"Insert and Retrieve User", testInsertAndRetrieveUser},
            {"Overwrite User Value", testOverwriteUserValue},
            {"Find User Method", testFindUserMethod},
            {"Erase User Method", testEraseUserMethod},
            {"Empty and Size User", testEmptyAndSizeUser},
            {"PriorityQueue Push", testPriorityQueuePush},
            {"PriorityQueue Pop", testPriorityQueuePop},
            {"PriorityQueue Top", testPriorityQueueTop},
            {"PriorityQueue Empty", testPriorityQueueEmpty},
            {"PriorityQueue Size", testPriorityQueueSize},

            {"Read All", testReadAll},
            {"Read Next", testReadNext},
            {"Find", testFind},
            {"Find No Matches", testFindNoMatches},

            {"PERFORMANCE TEST", run_performance_test}
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