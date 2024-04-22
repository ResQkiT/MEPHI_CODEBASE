#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include <vector>
#include <list>
#include <algorithm>
#include "DynamicArraySequence.h"

template <class T>
void printArr(DynamicArray<T> &arr)
{
    std::cout << "Mass:" << std::endl;
    for (auto b : arr)
    {
        std::cout << b << std::endl;
    }
}
// погуглить про explicit
//random acces iter
//bidirectional iterator

int main()
{
    /*


    int arr[5] = {7, -123, 3, 13, 5};
    DynamicArray<int> da(arr, 5);
    auto it = DynamicArray<int>::Iterator(da.begin());
    for (int i = 1; it != da.end(); i*=2, it ++)
    {
        *it = i;w
        printArr(da);
    }

    for (auto var: da)
    {
        std::cout << var << std::endl;
    }
    */
    //shared pointer
    int arr[5] = {7, -123, 3, 13, 5};
    DynamicArray<int> da(arr, 5);
    DynamicArraySequence<int> sequence(&da);
    std::cout << "end;" << std::endl;
    return 0;
}