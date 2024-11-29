#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <cassert>
#include "HashMap.hpp"

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
            {"Empty and Size User", testEmptyAndSizeUser}
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