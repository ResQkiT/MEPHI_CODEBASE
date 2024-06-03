#include <iostream>
#include <cassert>
#include <string>
#include <functional>
#include "BinaryTree.h"

namespace tests
{
    using namespace std;

    void create_binary_tree(){
        int arr[6] = {2, -1, 3, 10, 5, 58};
        BinaryTree<int> tree(arr, 6);
        assert(tree.get_size() == 6);
        tree.insert(3);
        assert(tree.get_size() == 6);
        tree.insert(66);
        assert(tree.get_size() == 7);
        tree.remove(-1);
        tree.remove(5);
        assert(tree.get_size() == 5);
    }
    void delete_binary_tree(){
        int arr[6] = {2, -1, 3, 10, 5, 58};
        BinaryTree<int> tree(arr, 6);
        assert(tree.get_size() == 6);
        tree.make_empty();
        assert(tree.get_size() == 0);
    }
    void merge_binary_tree(){
        int arr1[5] = {0 ,1 ,5, -7, 11};
        int arr2[6] = {- 8, 13, 12, 14, -20, -19};
        BinaryTree<int> tree1(arr1, 5);
        BinaryTree<int> tree2(arr2, 6);
        assert(tree1.get_size() == 5);
        assert(tree2.get_size() == 6);
        tree1.merge(tree2);
        assert(tree1.get_size() == 11);
        assert(tree2.get_size() == 6);
  
    }
    const static function<void(void)> test_functions[] = {
        create_binary_tree,
        delete_binary_tree,
        merge_binary_tree
    };
    void run(){
        cout << "Starting tests..." << endl;
        size_t function_number = 1;
        for(auto function : test_functions){
            function();
            cout << "Test "<< function_number << " passed!"<<endl;
            function_number++;
        }
        cout << "ALL TEST PASSED!" << endl;
    }
} // namespace tests

void start_tests(){

    tests::run();
}