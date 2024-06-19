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
#include "Set.h"

namespace tests
{
    using namespace std;

    class TestObject
    {
    private:
        bool is_called = false;
        int u = 0;

    public:
        TestObject() : u{0} {};
        TestObject(int u) : u{u} {};
        TestObject(const TestObject &other) : u{other.u}, is_called{other.is_called} {};
        void call()
        {
            is_called = true;
        }
        bool was_called()
        {
            return is_called;
        }
        bool operator<(const TestObject &other) const
        {
            return this->u < other.u;
        }
        bool operator>(const TestObject &other) const
        {
            return this->u > other.u;
        }
        bool operator==(const TestObject &other) const
        {
            return this->u == other.u;
        }
    };

    // test 1
    void create_binary_tree()
    {
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
    // test 2
    void delete_binary_tree()
    {
        int arr[6] = {2, -1, 3, 10, 5, 58};
        BinaryTree<int> tree(arr, 6);
        assert(tree.get_size() == 6);
        tree.make_empty();
        assert(tree.get_size() == 0);
    }
    // test 3
    void merge_binary_tree()
    {
        int arr1[5] = {0, 1, 5, -7, 11};
        int arr2[6] = {-8, 13, 12, 14, -20, -19};
        BinaryTree<int> tree1(arr1, 5);
        BinaryTree<int> tree2(arr2, 6);
        assert(tree1.get_size() == 5);
        assert(tree2.get_size() == 6);
        tree1.merge(tree2);
        assert(tree1.get_size() == 11);
        assert(tree2.get_size() == 6);
    }
    // test 4
    void test_pre_order()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
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
    // test 5
    void test_in_order()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_in_order_list[test_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
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
    // test 6
    void test_post_order()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_post_order_list[test_size] = {1, 2, 4, 3, 6, 7, 9, 10, 8, 5};
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
    // test 7
    void test_custom_order()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
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
    // test 8
    void test_post_order_exception()
    {
        BinaryTree<int> tree;
        assert(tree.get_size() == 0);
        DynamicArraySequence<int> darray;
        std::string order = "Rl";
        try
        {
            tree.custom_order(order, darray);
            assert(0);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    // test 9
    void test_avl_tree_initialization_and_insertion()
    {
        int arr[] = {1, 2, 3, 4};
        AvlTree<int> tree(arr, 4);
        assert(tree.get_size() == 4);
        tree.insert(-1);
        tree.insert(-1);
        assert(tree.get_size() == 5);
        tree.insert(15);
        assert(tree.get_size() == 6);
        tree.insert(0);
        assert(tree.get_size() == 7);
        tree.insert(1);
        assert(tree.get_size() == 7);
    }

    // test 10
    void test_avl_find()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        AvlTree<int> tree(arr, test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
    }
    // test 11
    void test_pre_order_avl()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_pre_order_list[test_size] = {5, 3, 2, 1, 4, 8, 7, 6, 10, 9};

        AvlTree<int> tree(arr, test_size);
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
    // test 12
    void test_in_order_avl()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_pre_order_list[test_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        AvlTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
        DynamicArraySequence<int> list;
        DynamicArraySequence<int> answerList(answer_pre_order_list, test_size);
        tree.in_order(list);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(list.get(i) == answerList.get(i));
        }
    }
    // test 13
    void test_post_order_avl()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_pre_order_list[test_size] = {1, 2, 4, 3, 6, 7, 9, 10, 8, 5};

        AvlTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(tree.find(arr[i]));
        }
        DynamicArraySequence<int> list;
        DynamicArraySequence<int> answerList(answer_pre_order_list, test_size);
        tree.post_order(list);
        for (size_t i = 0; i < test_size; i++)
        {
            assert(list.get(i) == answerList.get(i));
        }
    }
    // test 14
    void test_custom_order_avl()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_custom_order_list[test_size] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        AvlTree<int> tree(arr, test_size);
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
    // test 15
    void test_avl_tree_deletion()
    {
        size_t test_size = 10;
        int arr[test_size] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        AvlTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);
        DynamicArraySequence<int> list;
        tree.pre_order(list);
        tree.in_order(list);
        tree.post_order(list);
        for (size_t i = 0; i < test_size; i++)
        {
            tree.remove(arr[i]);
            assert(tree.get_size() == test_size - 1 - i);
        }
    }
    // test 16
    void test_binary_tree_iterator()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_list[test_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        BinaryTree<int> tree(arr, test_size);
        auto it = tree.begin();

        for (size_t i = 0; i < test_size; i++)
        {
            assert(answer_list[i] == *it);
            it++;
        }
    }
    // test 17
    void test_avl_tree_iterator()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer_list[test_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        AvlTree<int> tree(arr, test_size);
        auto it = tree.begin();

        for (size_t i = 0; i < test_size; i++)
        {
            assert(answer_list[i] == *it);
            it++;
        }
    }
    // test 18
    void test_binary_tree_map()
    {
        size_t test_size = 10;
        TestObject arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        auto function = [](TestObject obj)
        {
            obj.call();
            return obj;
        };

        BinaryTree<TestObject> tree(arr, test_size);
        assert(tree.get_size() == test_size);

        tree.map(function);
        assert(tree.get_size() == test_size);

        for (auto var : tree)
        {
            assert(var.was_called());
        }
    }
    // test 19
    void test_binary_tree_where()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        int answer[5] = {1, 3, 5, 7, 9};
        auto function = [](int a){ return a % 2 == 1; };

        BinaryTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);

        tree.where(function);
        assert(tree.get_size() == 5);

        auto it = tree.begin();
        for (size_t i = 0; i < tree.get_size(); i++)
        {
            assert(answer[i] == *it);
            it++;
        }
    }
    // test 20
    void test_binary_tree_reduce()
    {
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        auto function = [](int a, int b) { return a + b; };
        int correct_answer = 55;
        BinaryTree<int> tree(arr, test_size);
        assert(tree.get_size() == test_size);

        int value = tree.reduce(function);
        assert(value == correct_answer);
    }
    //test 21
    void test_binary_tree_equal(){
        size_t test_size = 3;
        int arr1[test_size] = {1, 2, 3};
        int arr2[test_size] = {3 ,2 ,1};
        BinaryTree<int> tree1(arr1, test_size);
        BinaryTree<int> tree2(arr2, test_size);
        assert(tree1.equal(tree1));
        assert(!tree1.equal(tree2)); //дерево можно задать по разному
    }
    //test 22
    void test_avl_tree_equal(){
        size_t test_size = 3;
        int arr1[test_size] = {1, 2, 3};
        int arr2[test_size] = {3 ,2 ,1};
        AvlTree<int> tree1(arr1, test_size);
        AvlTree<int> tree2(arr2, test_size);
        assert(tree1.equal(tree1));
        assert(tree1.equal(tree2));
    }
    //test 23
    void test_set_init(){
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        Set<int, AvlTree> set(arr, test_size);
        assert(set.size() == test_size);

        for (size_t i = 0; i < test_size; i++)
        {
            assert( set.find(arr[i]));
        }
    }
    //test 24
    void test_set_deletion(){
        size_t test_size = 10;
        int arr[test_size] = {5, 3, 8, 2, 4, 7, 10, 1, 6, 9};
        Set<int, AvlTree> set(arr, test_size);
        assert(set.size() == test_size);

        for (size_t i = 0; i < test_size; i++)
        {
            set.remove(arr[i]);
        }
        assert(set.size() == 0);
    }
    //test 25
    void test_set_union(){
        size_t size1 = 10;
        size_t size2 = 11;
        size_t answer_size = 15;
        int arr1[size1] = {1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10};
        int arr2[size2] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int answer_arr[answer_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        Set<int> set1(arr1, size1);
        Set<int> set2(arr2, size2);
        
        set1.set_union(set2);
        assert(set1.size() == answer_size);

        for (size_t i = 0; i < answer_size; i++)
        {
            assert(set1.find(answer_arr[i]));
        }
    }
    //test 26
    void test_set_intersection(){
        size_t size1 = 10;
        size_t size2 = 11;
        size_t answer_size = 6;
        int arr1[size1] = {1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10};
        int arr2[size2] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int answer_arr[answer_size] = {5, 6, 7, 8, 9, 10};
        Set<int> set1(arr1, size1);
        Set<int> set2(arr2, size2);
        
        set1.set_intersection(set2);
        assert(set1.size() == answer_size);

        for (size_t i = 0; i < answer_size; i++)
        {
            assert(set1.find(answer_arr[i]));
        }
    }
    //test 27
    void test_set_difference(){
        size_t size1 = 10;
        size_t size2 = 11;
        size_t answer_size = 4;
        int arr1[size1] = {1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10};
        int arr2[size2] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int answer_arr[answer_size] = {1, 2, 3, 4};
        Set<int> set1(arr1, size1);
        Set<int> set2(arr2, size2);
        
        set1.set_difference(set2);
        assert(set1.size() == answer_size);
        
        for (size_t i = 0; i < answer_size; i++)
        {
            assert(set1.find(answer_arr[i]));
        }
        
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
        test_avl_tree_initialization_and_insertion,
        test_avl_find,
        test_pre_order_avl,
        test_in_order,
        test_post_order,
        test_custom_order,
        test_avl_tree_deletion,
        test_binary_tree_iterator,
        test_avl_tree_iterator,
        test_binary_tree_map,
        test_binary_tree_where,
        test_binary_tree_reduce,
        test_binary_tree_equal,
        test_avl_tree_equal,
        test_set_init,
        test_set_deletion,
        test_set_union,
        test_set_intersection,
        test_set_difference
    };
    void run()
    {
        cout << "Starting tests..." << endl;
        size_t function_number = 1;
        for (auto function : test_functions)
        {
            function();
            cout << "Test " << function_number << " passed!" << endl;
            function_number++;
        }
        cout << "ALL TEST PASSED!" << endl;
    }
} // namespace tests

void start_tests()
{

    tests::run();
}