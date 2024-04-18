#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include <vector>
#include <list>
template<class T>
void printArr(LinkedList<T> & arr){

    for (;!arr.isEmpty();)
    {
        std::cout << arr.back() << std:: endl;
        arr.pop_back();
    }
}
int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> da(5, arr);
    auto it = DynamicArray<int> :: Iterator(da.begin());
    auto s = da.begin();
    
    for (; it!=da.end(); it++)
    {
        std::cout <<  *it << std::endl;
    }
    
    return 0;
}