#include <iostream>
#include "../Lab2/DynamicArray.h"
#include "Complex.hpp"
#include "test.h"
#include "../Lab2/readio.h"
#include "ActionHandler.h"
#include "adapters/AbstractAdapter.h"
#include "adapters/QueueAdapter.h"
#include "adapters/DequeAdapter.h"
#include "adapters/StackAdapter.h"
#include "adapters/SegmentedDequeAdapter.h"
#include "entities/Student.h" 
#include "Queue.hpp"
#include "Stack.hpp"
#include <string>

using namespace std;

void show_map_where_reduce_example(){
    //Очередь за комплексными обедами :)
    Student arr[10] = {
        {"John", "Smith", "john.smith@example.com", 1, 256},
        {"Sarah", "Johnson", "sarah.johnson@example.com", 2, 78},
        {"Michael", "Williams", "michael.williams@example.com", 3, 420},
        {"Emily", "Brown", "emily.brown@example.com", 4, 143},
        {"David", "Jones", "david.jones@example.com", 5, 349},
        {"Jessica", "Davis", "jessica.davis@example.com", 6, 87},
        {"Andrew", "Miller", "andrew.miller@example.com", 7, 205},
        {"Emma", "Wilson", "emma.wilson@example.com", 8, 92},
        {"Daniel", "Moore", "daniel.moore@example.com", 9, 431},
        {"Lisa", "Anderson", "lisa.anderson@example.com", 10, 176}
    };
    for (size_t i = 0; i < 10; i++)
    {
        cout << arr[i].get_name() + " " + arr[i].get_surname() + " , balance: " <<  arr[i].get_money() << endl;
    }
    
    Queue<Student> queue(arr, 10);
    auto is_enough_for_complex = [](Student student){
        return student.get_money()>=195;
    };
    queue.where(is_enough_for_complex);
    cout << "Lucky owners of complex lunch ->" << endl;
    while (!queue.empty())
    {
        cout << queue.front().get_name() + " " + queue.front().get_surname() + " , balance: " <<  queue.front().get_money() << endl;
        queue.pop();
    }
    
    
} 

int main(){
    start_tests();
    show_map_where_reduce_example();
    
}
/*
ActionHandler<int> handler(new QueueAdapter<int>());
    //handler.input_data().output_data();
    ActionHandler<int> handler2(new SegmentedDequeAdapter<int>());
    handler2.input_data().output_data();

*/