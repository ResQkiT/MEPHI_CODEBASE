#include "iostream"
#include "LinkedList.hpp"
#include "memory"
int main(){
    
    LinkedList<int> list;
    for (size_t i = 0; i < 10; i++)
    {
        list.push_back(i);
    }
    while (!list.is_empty() )
    {
        std::cout << list.back();
        list.pop_back();
    }
    
    


}