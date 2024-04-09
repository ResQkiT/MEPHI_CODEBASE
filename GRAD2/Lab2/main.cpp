#include <iostream>
#include "DynamicArray.h"
int main()
{
    int a[5] = {1,2,3,4,5};
    DynamicArray<int> dA(a, 5);
    std::cout << dA.getLength() << std::endl; 
    return 0;
}