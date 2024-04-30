#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "DynamicArraySequence.h"
#include "LinkedListSequence.h"

#include <cassert> 

namespace tests
{
    using namespace std;

    /// @brief checking is all f works correct;
    void test1(){
        int n1 = 3;
        int arr1[n1] = { 1 ,2 ,3 };
        DynamicArray<int> dynamic(arr1, n1);
        assert(dynamic.get_size() == n1);
        assert(dynamic[0] == arr1[0]);
        assert(dynamic[n1 - 1] == arr1[n1 - 1]);
        for (int i = 0; i < n1; i++)
        {
            assert(arr1[i] == dynamic[i]);
            assert(arr1[i] == dynamic.get(i));
        }
        cout << "TEST 1 PASSED!"<< endl;
    }

    //for test 2
    
    void test2(){
        int n2 = 3;
        int arr2[n2] = { 1 ,2 ,3 };
        LinkedList<int> linked(arr2, n2);
        assert(linked.get_size() == n2);
        assert(linked.front() == arr2[0]);
        assert(linked.back() == arr2[n2 - 1]);
        for (size_t i = 0; i < linked.get_size(); i++)
        {
            assert(arr2[i] == linked.get(i));
        }
        cout << "TEST 2 PASSED!"<< endl;
    }

    /// @brief checks if Dynamic Sequences works correct
    void test3(){
        int n3 = 5;
        int arr3[] = {1, 2, 3, 4, 5};
        DynamicArraySequence<int> d_sequence(arr3, n3);
        assert(d_sequence.get_length() == n3);
        for (size_t i = 0; i < d_sequence.get_length(); i++)
        {
            assert(d_sequence.get(i) == arr3[i]);
        }
        cout << "TEST 3 PASSED!"<< endl;
    }

    /// @brief checks if Linked Sequences works correct
    void test4(){
        int n4 = 5;
        int arr4[] = {9, 8, 7, 6, 5};
        LinkedListSequence<int> l_sequence(arr4, n4);
        assert(l_sequence.get_length() == n4);
        for (size_t i = 0; i < l_sequence.get_length(); i++)
        {
            assert(l_sequence.get(i) == arr4[i]);
        }
        
        cout << "TEST 4 PASSED!"<< endl;
    }

    /// @brief checks if append works correct in DynamicArraySequence
    void test5() {
        DynamicArraySequence<int> list;
        list.append(10);
        assert(list.get_length() == 1);
        assert(list.get(0) == 10);
        cout << "TEST 5 PASSED!"<< endl;
    }

    /// @brief checks if append works correct in LinkedListSequence
    void test6() {
        LinkedListSequence<int> list;
        list.append(10);
        assert(list.get_length() == 1);
        assert(list.get(0) == 10);
        cout << "TEST 6 PASSED!"<< endl;
    }

    /// @brief checks if prepand works correct in DynamicArraySequence
    void test7() {
        DynamicArraySequence<int> list;
        list.prepend(10);
        assert(list.get_length() == 1);
        assert(list.get(0) == 10);
        cout << "TEST 7 PASSED!"<< endl;
    }

    /// @brief checks if prepend works correct in LinkedListSequence
    void test8() {
        LinkedListSequence<int> list;
        list.prepend(10);
        assert(list.get_length() == 1);
        assert(list.get(0) == 10);
        cout << "TEST 8 PASSED!"<< endl;
    }

    /// @brief checks if concat works correct in DynamicArraySequence
    void test9(){
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        DynamicArraySequence<int> list1(arr1, 3);
        DynamicArraySequence<int> list2(arr2, 3);
        list1.concat(&list2);
        assert(list1.get_length() == 6);
        for (int i = 0; i < 3; ++i) {
            assert(list1.get(i) == arr1[i]);
        }
        for (int i = 3; i < 6; ++i) {
            assert(list1.get(i) == arr2[i - 3]);
        }
        cout << "TEST 9 PASSED!"<< endl;
    }

    /// @brief checks if concat works correct in LinkedListSequence
    void test10() {
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        LinkedListSequence<int> list1(arr1, 3);
        LinkedListSequence<int> list2(arr2, 3);
        list1.concat(&list2);
        assert(list1.get_length() == 6);
        for (int i = 0; i < 3; ++i) {
            assert(list1.get(i) == arr1[i]);
        }
        for (int i = 3; i < 6; ++i) {
            assert(list1.get(i) == arr2[i - 3]);
        }
        cout << "TEST 10 PASSED!"<< endl;
    }

    /// @brief checks if subs function work correct with args 0 0 in DynamicArraySequence
    void test11() {
        int arr[] = {1, 2 ,3};
        DynamicArraySequence<int> list(arr , 1);
        DynamicArraySequence<int> * subsequence = list.get_subsequence(0, 0);
        assert(subsequence->get_length() == 1);
        assert(subsequence->get(0) == arr[0]);

        cout << "TEST 11 PASSED!"<< endl;
    }

    /// @brief checks if subs function work correct with args 0 0 in LinkedListSequence
    void test12() {
        int arr[] = {3, 2 ,1};
        LinkedListSequence<int> list(arr , 1);
        LinkedListSequence<int> * subsequence = list.get_subsequence(0, 0);
        assert(subsequence->get_length() == 1);
        assert(subsequence->get(0) == arr[0]);
        
        cout << "TEST 12 PASSED!"<< endl;
    }

    /// @brief cheks if subs work correct with normal args in DynamicArraySequence
    void test13(){
        int arr[] = {1, 2, 3, 4, 5};
        DynamicArraySequence<int> list(arr, 5);
        DynamicArraySequence<int> * subsequence = list.get_subsequence(2, 4);
        assert(subsequence->get_length() == 3);
        for (int i = 0; i < subsequence->get_length(); ++i) {
            assert(subsequence->get(i) == arr[i + 2]);
        }
        
        cout << "TEST 13 PASSED!"<< endl;
    }

    /// @brief checks if subs work correct with normal args in LinkedListSequence
    void test14(){
        int arr[] = {1, 2, 3, 4, 5};
        LinkedListSequence<int> list(arr, 5);
        LinkedListSequence<int> * subsequence = list.get_subsequence(2, 4);
        assert(subsequence->get_length() == 3);
        for (int i = 0; i < subsequence->get_length(); ++i) {
            assert(subsequence->get(i) == arr[i + 2]);
        }
        
        cout << "TEST 14 PASSED!"<< endl;
    }

    /// @brief stress test for DynamicArraySequence
    void test15() {
        const int n = 1000;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
        DynamicArraySequence<int> list(arr, n);
        DynamicArraySequence<int> * subsequence1 = list.get_subsequence(0, n / 2);
        assert(subsequence1->get_length() == n / 2 + 1);
        for (int i = 0; i < subsequence1->get_length(); ++i) {
            assert(subsequence1->get(i) == arr[i]);
        }
        cout << "TEST 15 PASSED!"<< endl;
    }

    /// @brief stress test fot LinkedListSequence
    void test16() {
        const int n = 1000;
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
        LinkedListSequence<int> list(arr, n);
        LinkedListSequence<int> * subsequence1 = list.get_subsequence(0, n / 2);
        assert(subsequence1->get_length() == n / 2 + 1);
        for (int i = 0; i < subsequence1->get_length(); ++i) {
            assert(subsequence1->get(i) == arr[i]);
        }
        cout << "TEST 16 PASSED!"<< endl;
    }

    /// @brief checks if insert_at works correct in DynamicArraySequence
    void test17(){
        int arr[] = {1, 2, 3, 4, 5};
        DynamicArraySequence<int> list(arr, 5);
        list.insert_at(2, 6);
        assert(list.get_length() == 6);
        for (int i = 0; i < 2; ++i) {
            assert(list.get(i) == arr[i]);
        }
        assert(list.get(2) == 6);
        for (int i = 3; i < 5; ++i) {
            assert(list.get(i) == arr[i - 1]);
        }
        cout << "TEST 17 PASSED!"<< endl;
    }

    /// @brief checks if insert_at works correct in LinkedListSequence
    void test18(){
        int arr[] = {1, 2, 3, 4, 5};
        LinkedListSequence<int> list(arr, 5);
        list.insert_at(2, 6);
        assert(list.get_length() == 6);
        for (int i = 0; i < 2; ++i) {
            assert(list.get(i) == arr[i]);
        }
        assert(list.get(2) == 6);
        for (int i = 3; i < 5; ++i) {
            assert(list.get(i) == arr[i - 1]);
        }
        cout << "TEST 18 PASSED!"<< endl;
    }



} // namespace tests