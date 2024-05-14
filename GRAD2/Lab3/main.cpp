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
/*
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
*/
template<class T>
void run(ActionHandler<T> & handler){
    char working_choose;

    bool is_running = true;
    cout << "Handler " + handler.get_type() + " is running\n";
    while (is_running)
    {
        cout << "Choose command: \n1 - create data sequence\n2 - show data sequence\n \n q - for exit\n";
        console_get(working_choose);
        if(working_choose == '1'){
            handler.input_data();
        }else if(working_choose == '2'){
            handler.output_data();
        }else if(working_choose = 'q'){
            is_running = false;
        }
    }
}
template<class T> 
void set_adapter(ActionHandler<T> & handler){
    char adapter_choose;
    cout << "1 - stack \n2 - deque\n3 - queue\n4 - segmented deque\n";
    console_get(adapter_choose);
    AbstractAdapter<T> * adapter;
    if (adapter_choose == '1')
    {
        adapter = new StackAdapter<T>();
    }else if(adapter_choose == '2'){
        adapter = new DequeAdapter<T>();
    }else if(adapter_choose == '3'){
        adapter = new QueueAdapter<T>();
    }else if(adapter_choose == '4'){
        adapter = new SegmentedDequeAdapter<T>();
    }
    cout << adapter->get_type() << endl;
    handler.set_adapter(adapter);
}

int main(){
    //start_tests();
    //show_map_where_reduce_example();
    char type_choose;
    bool is_running = true;
    while(is_running){
        cout << "1 - int\n 2 - double\n 3 - char \n 4 - string"<<endl;
        console_get(type_choose);
        if (type_choose == '1'){
            ActionHandler<int> handler;
            set_adapter(handler);
            run(handler);
        }else if(type_choose == '2'){
            ActionHandler<double> handler;
            set_adapter(handler);
            run(handler);
        }else if(type_choose == '3'){
            ActionHandler<char> handler;
            set_adapter(handler);
            run(handler);
        }else if(type_choose == '4'){
            ActionHandler<string> handler;
            set_adapter(handler);
            run(handler);
        }else{
            continue;
        }
    }
}
/*
ActionHandler<int> handler(new QueueAdapter<int>());
    //handler.input_data().output_data();
    ActionHandler<int> handler2(new SegmentedDequeAdapter<int>());
    handler2.input_data().output_data();

*/