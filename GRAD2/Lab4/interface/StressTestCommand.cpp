#include "StressTestCommand.h"
#include <iostream>
#include <random>
#include <climits>
#include "../BinaryTree.h"
#include "../AvlTree.h"
#include <chrono>
#include <functional>

using namespace std;

StressTestCommand::StressTestCommand(/* args */)
{
}

StressTestCommand::~StressTestCommand() = default;

void stress_test_binary_tree(long long first_test_count )
{
    BinaryTree<int> tree;
    StressTestCommand::RandomGenerator generator(INT_MIN, INT_MAX);
    
    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < first_test_count; i++)
    {
        int random_number = generator.get();
        tree.insert(random_number);
    }
    auto end = std::chrono::steady_clock::now();
    
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    
    cout << "Inserting " << first_test_count << " elements in: " << elapsed_ms << endl;
}
void stress_test_avl_tree(long long first_test_count )
{
    AvlTree<int> tree;
    StressTestCommand::RandomGenerator generator(INT_MIN, INT_MAX);

    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < first_test_count; i++)
    {
        int random_number = generator.get();
        tree.insert(random_number);
    }
    auto end = std::chrono::steady_clock::now();
    
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    cout << "Inserting " << first_test_count << " elements in: " << elapsed_ms << " ms" << endl;
}
void StressTestCommand::exec()
{
    cout << "STARTING STRESS TEST" << endl;
    cout << "Testing binary tree normal data size" << endl;
    stress_test_binary_tree(1000000);
    cout << "Testing avl tree normal data size" << endl;
    stress_test_avl_tree(1000000);
}

StressTestCommand *StressTestCommand::clone()
{
    return new StressTestCommand();
}
