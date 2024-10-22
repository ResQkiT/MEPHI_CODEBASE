#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cassert>

#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/WeakPtr.hpp"
#include "smart_pointers/UniquePtr.hpp"
#include "LinkedListSequence.hpp"

namespace test_case{

    template<typename Func>
    double measureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
    }

    void testFunctionality(std::ostream& output_stream) {
        std::ostringstream oss;
        output_stream << "Test_ing functionality...\n";
        {
            output_stream << "  - SharedPtr: ";
            SharedPtr<int> ptr1(new int(5));
            assert(ptr1.get() != nullptr);
            assert(*ptr1 == 5);

            SharedPtr<int> ptr2(ptr1);
            assert(ptr1.get() == ptr2.get());
            assert(*ptr2 == 5);
            assert(ptr1.use_count() == 2);

            SharedPtr<int> ptr3;
            ptr3 = ptr1;
            assert(ptr3.get() == ptr1.get());
            assert(*ptr3 == 5);
            assert(ptr1.use_count() == 3);
            output_stream << "OK\n";
        }

        {
            output_stream << "  - WeakPtr: ";
            SharedPtr<int> SharedPtr(new int(10));
            WeakPtr<int> weekPtr;

            weekPtr = SharedPtr;
            assert(!weekPtr.expired());

            assert(*weekPtr.lock() == 10);

            SharedPtr.reset();
            output_stream << "OK\n";
        }

        {
            output_stream << "  - UniquePtr: ";
            UniquePtr<int> ptr1(new int(15));
            assert(ptr1.get() != nullptr);
            assert(*ptr1 == 15);

            UniquePtr<int> ptr2(std::move(ptr1));
            assert(ptr1.get() == nullptr);
            assert(ptr2.get() != nullptr);
            assert(*ptr2 == 15);

            output_stream << "OK\n";
        }
        output_stream << "Functionality tests passed!\n\n";
    }

    void testPerformance(std::ostream& output_stream) {
        const std::vector<size_t> objectCounts = { 100, 1000, 10000, 100000, 1000000 };

        output_stream << "---------------------------------------------------------------------------\n";
        output_stream << "|  count  |   SharedPtr   |  Raw Pointer  | std::shared_ptr |   UniquePtr     |\n";
        output_stream << "---------------------------------------------------------------------------\n";

        for (size_t objectCount : objectCounts) {
            double SharedPtrTime = measureTime([&objectCount]() {
                for (size_t i = 0; i < objectCount; ++i) {
                    SharedPtr<int> ptr(new int(i));
                }
            });

            double rawPtrTime = measureTime([&objectCount]() {
                for (size_t i = 0; i < objectCount; ++i) {
                    int* ptr = new int(i);
                    delete ptr;
                }
            });

            double stdSharedPtrTime = measureTime([&objectCount]() {
                for (size_t i = 0; i < objectCount; ++i) {
                    std::shared_ptr<int> ptr = std::make_shared<int>(i);
                }
            });

            double UniquePtrTime = measureTime([&objectCount]() {
                for (size_t i = 0; i < objectCount; ++i) {
                    UniquePtr<int> ptr(new int(i));
                }
            });

            output_stream << "| " << std::setw(10) << objectCount << " |";
            output_stream << std::setw(12) << SharedPtrTime << " ms |";
            output_stream << std::setw(14) << rawPtrTime << " ms |";
            output_stream << std::setw(15) << stdSharedPtrTime << " ms |";
            output_stream << std::setw(14) << UniquePtrTime << " ms |\n";
        }
        output_stream << "---------------------------------------------------------------------------\n";
    }
    void Test_append(std::ostream& output_stream) {
        output_stream << "Running Test_append..." << std::endl;
        LinkedListSequence<int> list;
        list.append(1);
        list.append(2);
        assert(list.get_length() == 2);
        assert(list.get_last() == 2);
        output_stream << "Test_append completed successfully." << std::endl;
    }

    void Test_prepend(std::ostream& output_stream) {
        output_stream << "Running Test_prepend..." << std::endl;
        LinkedListSequence<int> list;
        list.prepend(1);
        assert(list.get_length() == 1);
        assert(list.get_first() == 1);
        list.prepend(2);
        assert(list.get_length() == 2);
        assert(list.get_first() == 2);
    output_stream << "Test_prepend completed successfully." << std::endl;
    }

    void Test_get_subsequence(std::ostream& output_stream) {
        output_stream << "Running Test_get_subsequence..." << std::endl;
        LinkedListSequence<int> list;
        for (int i = 1; i <= 5; ++i) {
            list.append(i);
        }
        UniquePtr<Sequence<int>> sub = list.get_subsequence(1, 3);
        std::cout << sub->get_length();
        // assert(sub->get_length() == 2);
        // for (size_t i = 0; i < sub->get_length(); ++i) {
        //     assert(sub->get(i) == i + 2);
        // }
        // output_stream << "Test_get_subsequence completed successfully." << std::endl;
    }

    void Test_insert_at(std::ostream& output_stream) {
        output_stream << "Running Test_insert_at..." << std::endl;
        LinkedListSequence<int> list;
        for (int i = 1; i <= 3; ++i) {
            list.append(i);
        }
        list.insert_at(4, 2);
        assert(list.get_length() == 4);
        assert(list.get(2) == 4);
        output_stream << "Test_insert_at completed successfully." << std::endl;
    }

    void Test_get_first(std::ostream& output_stream) {
        output_stream << "Running Test__get_first..." << std::endl;
        LinkedListSequence<int> list;
        list.append(1);
        assert(list.get_first() == 1);
        output_stream << "Test_get_first completed successfully." << std::endl;
    }

    void Test_get_last(std::ostream& output_stream) {
        output_stream << "Running Test_get_last..." <<std::endl;
        LinkedListSequence<int> list;
        list.append(1);
        assert(list.get_last() == 1);
        list.append(2);
        assert(list.get_last() == 2);
        output_stream << "Test_get_last completed successfully." << std::endl;
    }

    void Test_get(std::ostream& output_stream) {
        output_stream << "Running Test_get..." << std::endl;
        LinkedListSequence<int> list;
        for (int i = 1; i <= 5; ++i) {
            list.append(i);
        }
        assert(list.get(3) == 4);
        output_stream << "Test_get completed successfully." << std::endl;
    }

    void Test_get_length(std::ostream& output_stream) {
        output_stream << "Running Test_get_length..." << std::endl;
        LinkedListSequence<int> list;
        assert(list.get_length() == 0);
        list.append(1);
        assert(list.get_length() == 1);
        output_stream << "Test_get_length completed successfully." << std::endl;
    }

    void testLinkedListSequence(std::ostream& output_stream) {
        Test_append(output_stream);
        Test_prepend(output_stream);
        Test_insert_at(output_stream);
        Test_get_first(output_stream);
        Test_get_last(output_stream);
        Test_get(output_stream);
        Test_get_length(output_stream);
        Test_get_subsequence(output_stream);
    }

}

void run_tests(std::ostream& output_stream) {
    test_case::testFunctionality(output_stream);
    test_case::testPerformance(output_stream);
    test_case::testLinkedListSequence(output_stream);
    output_stream << "Tests completed successfully." << std::endl;
    output_stream <<"--------------------------------------------------------------"<< std::endl;
}