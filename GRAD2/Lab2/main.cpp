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
    int arr1[5] = {1, 2, 3 ,4 ,5 };
    int arr2[6] = {6, 7, 8 ,9 ,10, 11};
    DynamicArraySequence das1(arr1, 5);
    DynamicArraySequence das2(arr2, 6);

    
    //sequence.add_from(da);
    std::cout << das2 + das1<<  " " << std::endl;
    return 0;
}