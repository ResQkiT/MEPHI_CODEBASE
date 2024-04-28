#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include <vector>
#include <list>
#include <algorithm>
#include "DynamicArraySequence.h"
#include "LinkedListSequence.h"

template <class T>
void printArr(Sequence<T> &arr)
{
    for (size_t i = 0; i < arr.get_length(); i++)
    {
        std::cout << arr.get(i) << " "; 
    }
    std::cout << std::endl;
    
}
template <class T>
void printArr(Sequence<T> * arr)
{
    for (size_t i = 0; i < arr->get_length(); i++)
    {
        std::cout << arr->get(i) << " "; 
    }
    std::cout << std::endl;
}
template<class T>
void printArr(LinkedList<T> & l){
    for(auto v: l ){
        std::cout << v << " ";
    }
}
int main()
{
    int arr1[5] = {1, 2, 3 ,4 ,5 };
    int arr2[6] = {6, 7, 8 ,9 ,10, 11};
    LinkedListSequence<int> das1(arr1, 5);
    LinkedListSequence<int> das2(arr2, 6);
    printArr(das1.append(das2));
    return 0;
}