#include <iostream>
#include "Lab1/smart_pointers/WeakPtr.hpp"
#include "Lab1/smart_pointers/SharedPtr.hpp"
#include <cassert>
using namespace std;

int main(){
    cout << "  - WeakPtr: ";
    SharedPtr<int> SharedPtr(new int(10));
    WeakPtr<int> weekPtr;

    weekPtr = SharedPtr;
    assert(!weekPtr.expired());

    assert(*weekPtr.lock() == 10);

    SharedPtr.reset();
    cout << "OK\n";

}