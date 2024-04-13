#include <iostream>
#include "DynamicArray.h"
#include <vector>
template<class T>
void printArr(DynamicArray<T> & arr){

    for (int i = 0; i < arr.get_size(); i++)
    {
        std::cout << arr[i] << std:: endl;
    }
}
int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> a(5, arr);
    
    DynamicArray<int> b;
    DynamicArray<int> c;
    c = b = a;
    
    std::cout << a.get_size();
    
    

    return 0;
}