#include <iostream>
#include <cassert>
#include <string>
#include <functional>
#include <string>
#include "BinaryTree.h"
#include "../Lab2/Sequence.h"
#include "../Lab2/DynamicArraySequence.h"
#include "../Lab2/LinkedListSequence.h"
#include "AvlTree.h"

namespace tests
{
    using namespace std;
    //test 1
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
    //test 2
    void delete_binary_tree(){
        int arr[6] = {2, -1, 3, 10, 5, 58};
        BinaryTree<int> tree(arr, 6);
        assert(tree.get_size() == 6);
        tree.make_empty();
        assert(tree.get_size() == 0);
    }
    //test 3
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
    //test 4
    void test_pre_order(){
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1 , 6, 9};
        int answer_pre_order_list[test_size] = {5, 3, 2, 1, 4, 8, 7, 6, 10, 9};
        BinaryTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
        DynamicArraySequence<int> list;
        DynamicArraySequence<int> answerList(answer_pre_order_list, test_size);
        tree.pre_order(list);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(list.get(i) == answerList.get(i));
        }
    }
    //test 5
    void test_in_order(){
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1 , 6, 9};
        int answer_in_order_list[test_size] = {1 , 2, 3, 4, 5, 6, 7, 8, 9 , 10};
        BinaryTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
        DynamicArraySequence<int> list;
        DynamicArraySequence<int> answerList(answer_in_order_list, test_size);
        tree.in_order(list);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(list.get(i) == answerList.get(i));
        }
    }
    //test 6
    void test_post_order(){
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1 , 6, 9};
        int answer_post_order_list[test_size] = {1, 2, 4, 3, 6, 7, 9, 10, 8, 5 };
        BinaryTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
        DynamicArraySequence<int> list;
        DynamicArraySequence<int> answerList(answer_post_order_list, test_size);
        tree.post_order(list);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(list.get(i) == answerList.get(i));
        }
    }
    //test 7
    void test_custom_order(){
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1 , 6, 9};
        int answer_custom_order_list[test_size] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        BinaryTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
        DynamicArraySequence<int> list;
        DynamicArraySequence<int> answerList(answer_custom_order_list, test_size);
        std::string order = "rRl";
        tree.custom_order(order, list);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(list.get(i) == answerList.get(i));
        }
    }
    //test 8
    void test_post_order_exception(){
        BinaryTree<int> tree;
        assert(tree.get_size() == 0);
        DynamicArraySequence<int> darray;
        std::string order = "Rl";
        try
        {
            tree.custom_order(order, darray);
            assert(0);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    //test 9
    void test_balance(){
        size_t test_size = 10;
        int arr[test_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        BinaryTree<int> tree(arr, test_size);
        DynamicArraySequence<int> list;
        tree.pre_order(list);
        tree.in_order(list);
        tree.post_order(list);
        tree.balance();
        std::cout << "After:" << std::endl;
        tree.pre_order(list);
        tree.in_order(list);
        tree.post_order(list);
        }
    const static function<void(void)> test_functions[] = {
        create_binary_tree,
        delete_binary_tree,
        merge_binary_tree,
        test_pre_order,
        test_in_order,
        test_post_order,
        test_custom_order,
        test_post_order_exception,
        test_balance
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