#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cassert>

#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/WeekPtr.hpp"
#include "smart_pointers/UniquePtr.hpp"
#include "LinkedListSequence.hpp"

template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
}

void testFunctionality() {
    std::cout << "Test_ing functionality...\n";
    {
        std::cout << "  - SharedPtr: ";
        SharedPtr<int> ptr1(new int(5));
        assert(ptr1.get() != nullptr);
        assert(*ptr1 == 5);

        SharedPtr<int> ptr2(ptr1);
        assert(ptr1.get() == ptr2.get());
        assert(*ptr2 == 5);
        assert(ptr1.get_ref_count() == 2);

        SharedPtr<int> ptr3;
        ptr3 = ptr1;
        assert(ptr3.get() == ptr1.get());
        assert(*ptr3 == 5);
        assert(ptr1.get_ref_count() == 3);
        std::cout << "OK\n";
    }

    {
        std::cout << "  - WeekPtr: ";
        SharedPtr<int> SharedPtr(new int(10));
        WeekPtr<int> weekPtr;

        weekPtr = SharedPtr;
        assert(!weekPtr.expired());

        assert(*weekPtr == 10);

        SharedPtr.reset();
        std::cout << "OK\n";
    }

    {
        std::cout << "  - UniquePtr: ";
        UniquePtr<int> ptr1(new int(15));
        assert(ptr1.get() != nullptr);
        assert(*ptr1 == 15);

        UniquePtr<int> ptr2(std::move(ptr1));
        assert(ptr1.get() == nullptr);
        assert(ptr2.get() != nullptr);
        assert(*ptr2 == 15);

        std::cout << "OK\n";
    }
    std::cout << "Functionality tests passed!\n\n";
}

void testPerformance() {
    const std::vector<size_t> objectCounts = { 100, 1000, 10000, 100000, 1000000 };

    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << "|  count  |   SharedPtr   |  Raw Pointer  | std::shared_ptr |   UniquePtr     |\n";
    std::cout << "---------------------------------------------------------------------------\n";

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

        std::cout << "| " << std::setw(10) << objectCount << " |";
        std::cout << std::setw(12) << SharedPtrTime << " ms |";
        std::cout << std::setw(14) << rawPtrTime << " ms |";
        std::cout << std::setw(15) << stdSharedPtrTime << " ms |";
        std::cout << std::setw(14) << UniquePtrTime << " ms |\n";
    }
    std::cout << "---------------------------------------------------------------------------\n";
}
void Test_append() {
    std::cout << "Running Test_append..." << std::endl;
    LinkedListSequence<int> list;
    list.append(1);
    list.append(2);
    assert(list.get_length() == 2);
    assert(list.get_last() == 2);
    std::cout << "Test_append completed successfully." << std::endl;
}

void Test_prepend() {
    std::cout << "Running Test_prepend..." << std::endl;
    LinkedListSequence<int> list;
    list.prepend(1);
    assert(list.get_length() == 1);
    assert(list.get_first() == 1);
    list.prepend(2);
    assert(list.get_length() == 2);
    assert(list.get_first() == 2);
   std::cout << "Test_prepend completed successfully." << std::endl;
}

void Test_get_subsequence() {
    std::cout << "Running Test_get_subsequence..." << std::endl;
    LinkedListSequence<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.append(i);
    }
    UniquePtr<Sequence<int>> sub = list.get_subsequence(1, 3);
    assert(sub->get_length() == 2);
    for (size_t i = 0; i < sub->get_length(); ++i) {
        assert(sub->get(i) == i + 2);
    }
    std::cout << "Test_get_subsequence completed successfully." << std::endl;
}

void Test_insert_at() {
    std::cout << "Running Test_insert_at..." << std::endl;
    LinkedListSequence<int> list;
    for (int i = 1; i <= 3; ++i) {
        list.append(i);
    }
    list.insert_at(4, 2);
    assert(list.get_length() == 4);
    assert(list.get(2) == 4);
    std::cout << "Test_insert_at completed successfully." << std::endl;
}

void Test_get_first() {
    std::cout << "Running Test__get_first..." << std::endl;
    LinkedListSequence<int> list;
    list.append(1);
    assert(list.get_first() == 1);
    std::cout << "Test_get_first completed successfully." << std::endl;
}

void Test_get_last() {
    std::cout << "Running Test_get_last..." <<std::endl;
    LinkedListSequence<int> list;
    list.append(1);
    assert(list.get_last() == 1);
    list.append(2);
    assert(list.get_last() == 2);
    std::cout << "Test_get_last completed successfully." << std::endl;
}

void Test_get() {
    std::cout << "Running Test_get..." << std::endl;
    LinkedListSequence<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.append(i);
    }
    assert(list.get(3) == 4);
    std::cout << "Test_get completed successfully." << std::endl;
}

void Test_get_length() {
    std::cout << "Running Test_get_length..." << std::endl;
    LinkedListSequence<int> list;
    assert(list.get_length() == 0);
    list.append(1);
    assert(list.get_length() == 1);
    std::cout << "Test_get_length completed successfully." << std::endl;
}

void testLinkedListSequence() {
    Test_append();
    Test_prepend();
    Test_get_subsequence();
    Test_insert_at();
    Test_get_first();
    Test_get_last();
    Test_get();
    Test_get_length();
}

void run_tests() {
    testFunctionality();
    testPerformance();
    testLinkedListSequence();
    std::cout << "Tests completed successfully." << std::endl;
    std::cout <<"--------------------------------------------------------------"<< std::endl;
}