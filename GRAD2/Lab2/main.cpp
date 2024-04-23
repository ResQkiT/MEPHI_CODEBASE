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
    da.clear();
    da.push_back(1);
    da.push_back(2);
    DynamicArraySequence<int> sequence;
    sequence.append(1);
    sequence.append(2);
    sequence.append(3);
    sequence.append(4);
    sequence.prepend(5);
    sequence.prepend(6);
    sequence.insertAt(3, 900);
    sequence.insertAt(1, 100);
    
    //sequence.add_from(da);
    std::cout << sequence<< " " << std::endl;
    DynamicArraySequence<int> * sub = sequence.getSubsequence(1, 5);
    std::cout <<  *sub ;

    return 0;
}