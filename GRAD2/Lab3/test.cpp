#include <iostream>
#include <cassert>
#include <string>
#include "Complex.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "../Lab2/DynamicArraySequence.h"
#include "../Lab2/LinkedListSequence.h"
#include "Deque.hpp"
#include "SegmentedDeque.hpp"
#include "entities/Person.h"

namespace tests
{
    using namespace std;
    // Complex number operation
    void test1()
    {
        Complex<int> a(5, 2);
        Complex<int> b(-1, -3);
        assert(!(a == b));
        assert(a.get_real() == 5 && a.get_imaginary() == 2);
        assert(a + b == Complex<int>(4, -1));
        assert(a - b == Complex<int>(6, 5));
        assert(a * b == Complex<int>(1, -17));

        cout << "Test 1 passed!" << endl;
    }

    // test how queue works
    void test2()
    {
        int arr[] = {1, 2, 3};
        Queue<int> q1(arr, 3);
        assert(q1.size() == 3);
        assert(q1.front() == arr[0]);
        assert(q1.back() == arr[2]);
        q1.pop();
        assert(q1.front() == arr[1]);
        q1.push(9);
        assert(q1.back() == 9);
        cout << "Test 2 passed!" << endl;
    }

    // test how map func works
    void test3()
    {
        int arr[] = {1, 2, 3, 4, 5};
        int answer[] = {2, 2, 6, 4, 10};
        Queue<int> q1(arr, 5);
        auto f1 = [](int a)
        {
            if (a % 2 == 0)
                return a;
            else
                return a * 2;
        };
        q1.map(f1);
        assert(q1.size() == 5);
        size_t i = 0;
        while (!q1.empty())
        {
            int temp = q1.front();
            q1.pop();
            assert(temp == answer[i]);
            i++;
        }
        cout << "Test 3 passed!" << endl;
    }

    // test how where func works
    void test4()
    {
        int arr[] = {1, 2, 3, 4, 5, 999};
        int answer[] = {1, 3, 5, 999};
        Queue<int> q1(arr, 6);
        auto f1 = [](int a)
        { return a % 2 == 1; };
        q1.where(f1);
        assert(q1.size() == 4);
        size_t i = 0;
        while (!q1.empty())
        {
            int temp = q1.front();
            q1.pop();
            assert(temp == answer[i]);
            i++;
        }

        cout << "Test 4 passed!" << endl;
    }
    // test how reduce works
    void test5()
    {
        int arr[] = {1, 2, 3};
        Queue<int> q1(arr, 3);
        auto f1 = [](int a, int b)
        { return 2 * a + 3 * b; };
        assert(q1.reduce(f1, 4) == 144);
        cout << "Test 5 passed!" << endl;
    }

    // test safe concatination
    void test6()
    {
        int arr1[] = {0, 1, 2, 3};
        int arr2[] = {4, 5, 6, 7, 8, 9, 10};
        Queue<int> q1(arr1, 4);
        Queue<int> q2(arr2, 7);
        q1.safe_concat(q2);
        assert(q2.size() == 7);
        assert(q1.size() == 11);
        size_t i = 0;
        while (!q1.empty())
        {
            assert(q1.front() == i);
            q1.pop();
            i++;
        }
        cout << "Test 6 passed!" << endl;
    }
    // test unsafe concat
    void test7()
    {
        int arr1[] = {0, 1, 2, 3};
        int arr2[] = {4, 5, 6, 7, 8, 9, 10};
        Queue<int> q1(arr1, 4);
        Queue<int> q2(arr2, 7);
        q1.force_concat(q2);
        assert(q2.size() == 0);
        assert(q1.size() == 11);
        size_t i = 0;
        while (!q1.empty())
        {
            assert(q1.front() == i);
            q1.pop();
            i++;
        }
        cout << "Test 7 passed!" << endl;
    }
    // test how Stack work
    void test8()
    {
        int arr[] = {1, 2, 3};
        Stack<int> a(arr, 3);
        assert(!a.empty());
        assert(a.size() == 3);
        assert(a.top() == 3);
        size_t index = 2;
        while (!a.empty())
        {
            assert(a.top() == arr[index]);
            a.pop();
            index--;
        }
        cout << "Test 8 passed!" << endl;
    }
    void test9()
    {
        int answer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        Stack<int> a;
        assert(a.empty());
        assert(a.size() == 0);
        for (size_t i = 10; i > 0; i--)
        {
            a.push(i);
        }

        size_t index = 0;
        while (!a.empty())
        {
            assert(a.top() == answer[index]);
            a.pop();
            index++;
        }

        cout << "Test 9 passed!" << endl;
    }

    // test how stack map f works
    void test10()
    {
        int arr[] = {1, 2, 3, 4, 5};
        int answer[] = {2, 2, 6, 4, 10};
        Stack<int> q1(arr, 5);
        auto f1 = [](int a)
        {
            if (a % 2 == 0)
                return a;
            else
                return a * 2;
        };
        q1.map(f1);
        assert(q1.size() == 5);
        size_t i = 4;
        while (!q1.empty())
        {
            int temp = q1.top();
            q1.pop();
            assert(temp == answer[i]);
            i--;
        }
        cout << "Test 10 passed!" << endl;
    }

    // test how stack where f works
    void test11()
    {
        int arr[] = {1, 2, 3, 4, 5, 999};
        int answer[] = {1, 3, 5, 999};
        Queue<int> q1(arr, 6);
        auto f1 = [](int a)
        { return a % 2 == 1; };
        q1.where(f1);
        assert(q1.size() == 4);
        size_t i = 0;
        while (!q1.empty())
        {
            int temp = q1.front();
            q1.pop();
            assert(temp == answer[i]);
            i++;
        }

        cout << "Test 11 passed!" << endl;
    }
    // test how stack reduce f works
    void test12()
    {
        int arr[] = {3, 2, 1};
        Stack<int> q1(arr, 3);
        auto f1 = [](int a, int b)
        { return 2 * a + 3 * b; };
        assert(q1.reduce(f1, 4) == 144);
        cout << "Test 12 passed!" << endl;
    }

    // test how deque works
    void test13()
    {
        int arr[] = {3, 2, 1};
        Deque<int> q1(arr, 3);
        assert(!q1.empty());
        assert(q1.front() == arr[0]);
        assert(q1.back() == arr[2]);
        assert(q1.size() == 3);
        for (int index = 0; index < q1.size(); index++)
        {
            assert(q1[index] == arr[index]);
        }

        cout << "Test 13 passed!" << endl;
    }
    // test map where reduce complex
    void test14()
    {
        int arr[] = {1, 2, 3, 4, 5};
        int answer[] = {2, 2, 6, 4, 10};
        Deque<int> q1(arr, 5);
        auto f1 = [](int a)
        {
            if (a % 2 == 0)
                return a;
            else
                return a * 2;
        };
        q1.map(f1);
        assert(q1.size() == 5);
        for (size_t i = 0; i < q1.size(); i++)
        {
            assert(q1[i] == answer[i]);
        }
        cout << "Test 14 passed!" << endl;
    }
    void test15()
    {
        int arr[] = {1, 2, 3, 4, 5, 999};
        int answer[] = {1, 3, 5, 999};
        Deque<int> q1(arr, 6);
        auto f1 = [](int a)
        { return a % 2 == 1; };
        q1.where(f1);
        assert(q1.size() == 4);
        for (size_t i = 0; i < q1.size(); i++)
        {
            assert(q1[i] == answer[i]);
        }
        cout << "Test 15 passed!" << endl;
    }
    void test16()
    {
        int arr[] = {1, 2, 3};
        Deque<int> q1(arr, 3);
        auto f1 = [](int a, int b)
        { return 2 * a + 3 * b; };
        assert(q1.reduce(f1, 4) == 144);
        cout << "Test 16 passed!" << endl;
    }
    // test Segmented Deque work
    void test17()
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        SegmentedDeque<int> sd(arr, 10, 3);
        // cout << sd.get_segment_size();
        assert(sd.get_segment_size() == 3);
        assert(sd.size() == 10);
        assert(sd.number_of_segments() == 4);
        assert(sd.back() == 10);
        assert(sd.front() == 1);
        sd.pop_front();
        sd.pop_back();
        assert(sd.size() == 8);
        assert(sd.front() == 2);
        assert(sd.back() == 9);
        sd.push_front(1);
        sd.push_back(10);
        for (size_t i = 0; i < 10; i++)
        {
            assert(sd[i] == arr[i]);
        }
        cout << "Test 17 passed!" << endl;
    }
    //test how append func work in segmented deque
    void test18(){
        int arr1[] = {1, 2, 3, 4, 5};
        int arr2[] = {6, 7, 8, 9, 10, 11};
        SegmentedDeque<int> sd1(arr1, 5, 2);
        SegmentedDeque<int> sd2(arr2, 6, 4);
        sd1.append_from(sd2);
        assert(sd2.size() == 6);
        assert(sd1.size() == 11);
        for (size_t i = 1; i <= sd1.size(); i++)
        {
            assert(sd1[i - 1] == i);
        }
        cout << "Test 18 passed!" << endl;
    }


    void run()
    {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
        test9();
        test10();
        test11();
        test12();
        test13();
        test14();
        test15();
        test16();
        test17();
        test18();
        cout << "ALL TEST PASSED!" << endl;
    }
} // namespace tests
void start_tests(){
    tests::run();
}