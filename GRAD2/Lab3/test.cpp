#include <iostream>
#include <cassert>
#include <string>
#include "Complex.hpp"
#include "Queue.hpp"

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
    //test unsafe concat
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
    void test8()
    {
    }
    void test9()
    {
    }
    void test10()
    {
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
        cout << "ALL TEST PASSED!" << endl;
    }
} // namespace tests

int main()
{
    std::cout << "Testing..." << std::endl;
    tests::run();
}