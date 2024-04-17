#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include <vector>
template<class T>
void printArr(LinkedList<T> & arr){

    for (; !arr.isEmpty();)
    {
        std::cout << arr.back() << std:: endl;
        arr.pop_back();
    }
}
int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    LinkedList<int> Ll(5, arr);
    LinkedList<int> A = std::move(Ll);
    printArr(A);    
    printArr(Ll);

    return 0;
}