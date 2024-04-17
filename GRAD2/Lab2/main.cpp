#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
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
    LinkedList<int> Ll(5, arr);
    LinkedList<int> A(Ll);
    Ll.push_front(99);
    Ll.push_back(-115);
    Ll.push_front(-1213);
    Ll.print();
    A.print();
    std::cout << Ll.getSize()<< std::endl;
    

    return 0;
}