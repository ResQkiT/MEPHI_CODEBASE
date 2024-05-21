#include <iostream>
#include <cassert>
#include <string>
#include <functional>
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
    class TestObject{
    private:
        bool is_called = false;
    
    public:
        int u = 0;
        TestObject() : u{0}{};
        TestObject(int u) : u{u}{};
        TestObject(const TestObject & other): u{other.u}, is_called{other.is_called}{};
        void call(){
            is_called = true;
        }
        bool was_called(){
            return is_called;
        }

    };
    using namespace std;
    // Complex number operation
    void test_complex_number_operations()
    {
        Complex<int> a(5, 2);
        Complex<int> b(-1, -3);
        assert(!(a == b));
        assert(a.get_real() == 5 && a.get_imaginary() == 2);
        assert(a + b == Complex<int>(4, -1));
        assert(a - b == Complex<int>(6, 5));
        assert(a * b == Complex<int>(1, -17));
    }

    // test how queue works
    void test_queue_work()
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
    }

    // test how map func works
    void test_queue_map()
    {
        TestObject arr[] = {1, 2, 3, 4, 5};
        Queue<TestObject> q1(arr, 5);
        auto f1 = [](TestObject a)
        {
            a.call();
            return a;
        };

        q1.map(f1);
        assert(q1.size() == 5);
        while (!q1.empty())
        {
            TestObject temp = q1.front();
            assert(temp.was_called());
            q1.pop();
        }
    }

    // test how where func works
    void test_queue_where()
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
    }
    // test how reduce works
    void test_queue_reduce()
    {
        int arr[] = {1, 2, 3};
        Queue<int> q1(arr, 3);
        auto f1 = [](int a, int b) 
        { return 2 * a + 3 * b; };
        assert(q1.reduce(f1, 4) == 144);
    }

    // test safe concatenation
    void test_queue_concatenation()
    {
        int arr1[] = {0, 1, 2, 3};
        int arr2[] = {4, 5, 6, 7, 8, 9, 10};
        Queue<int> q1(arr1, 4);
        Queue<int> q2(arr2, 7);
        q1.concat(q2);
        assert(q2.size() == 7);
        assert(q1.size() == 11);
        size_t i = 0;
        while (!q1.empty())
        {
            assert(q1.front() == i);
            q1.pop();
            i++;
        }
    }
    // test how Stack work
    void test_stack_work()
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
    }
    void test_stack_push_back()
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

    }

    // test how stack map f works
    void test_stack_map()
    {
        TestObject arr[] = {1, 2, 3, 4, 5}; // 
        Stack<TestObject> q1(arr, 5);
        
        auto f1 = [](TestObject a)
        {
            a.call();
            return a;
        };

        q1.map(f1);
        
        assert(q1.size() == 5);
        while (!q1.empty())
        {
            TestObject temp = q1.top();
            assert(temp.was_called());
            q1.pop();
        }
    }

    // test how stack where f works
    void test_stack_where()
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
    }
    // test how stack reduce f works
    void test_stack_reduce()
    {
        int arr[] = {3, 2, 1};
        Stack<int> q1(arr, 3);
        auto f1 = [](int a, int b)
        { return 2 * a + 3 * b; };
        assert(q1.reduce(f1, 4) == 144);
    }

    // test how deque works
    void test_deque_works()
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
    }
    void test_deque_concat(){
        int arr1[] = {1, 2, 3};
        int arr2[] = {4, 5, 6};
        Deque<int> d1(arr1, 3);
        Deque<int> d2(arr2, 3);
        d1.concat(d2);
        assert(d1.size() == 6);
        assert(d2.size() == 3);
        for (size_t i = 0; i < d1.size(); i++)
        {
            assert(d1[i] == i + 1);
        }
    }
    // test map where reduce complex
    void test_deque_map()
    {
        TestObject arr[] = {1, 2, 3, 4, 5};
        Deque<TestObject> q1(arr, 5);
        auto f1 = [](TestObject a)
        {
            a.call();
            return a;
        };
        q1.map(f1);
        assert(q1.size() == 5);
        for (size_t i = 0; i < q1.size(); i++)
        {
            assert(q1[i].was_called());
        }
    }
    void test_deque_where()
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
    }
    void test_deque_reduce()
    {
        int arr[] = {1, 2, 3};
        Deque<int> q1(arr, 3);
        auto f1 = [](int a, int b)
        { return 2 * a + 3 * b; };
        assert(q1.reduce(f1, 4) == 144);
    }
    // test Segmented Deque work
    void test_segmented_deque()
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
    }
    //test how append func work in segmented deque
    void test_segmented_deque_append_from(){
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
    }
    const static function<void(void)> test_functions[] ={
            test_complex_number_operations,
            test_queue_work,
            test_queue_map,
            test_queue_where,
            test_queue_reduce,
            test_queue_concatenation,
            test_stack_work,
            test_stack_push_back,
            test_stack_map,
            test_stack_where,
            test_stack_reduce,
            test_deque_works,
            test_deque_concat,
            test_deque_map,
            test_deque_where,
            test_deque_reduce,
            test_segmented_deque,
            test_segmented_deque_append_from
    };

    void run()
    {
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