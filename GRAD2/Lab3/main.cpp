#include <iostream>
#include "../Lab2/DynamicArray.h"
#include "Complex.hpp"
#include "test.h"
#include "../ExtendedMenu/readio.h"
#include "ActionHandler.h"


#include "entities/Student.h" 
#include "Queue.hpp"
#include <string>
#include "../ExtendedMenu/Menu.h"
#include "../ExtendedMenu/ICommand.h"  
#include "interface/StartTestCommand.h"
#include "interface/StartDialogCommand.h"
#include "interface/RunFunctionCommand.h"

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
    cout<< "We have created a queue of student, stand`s in a queue in MEPHI cafeteria:" <<endl;
    Queue<Student> queue(arr, 10);
    for (size_t i = 0; i < 10; i++)
    {
        cout << arr[i].get_name() + " " + arr[i].get_surname() + " , balance: " <<  arr[i].get_money() << endl;
    }
    cout<< endl << "Now, lets check how many of them could buy a standard 'complex lunch' using <where> function" << endl ;
    
    auto is_enough_for_complex = [](Student student){
        return student.get_money()>=195;
    };
    Queue<Student> queue_copy(queue);
    queue_copy.where(is_enough_for_complex);
    cout << endl<<"Lucky owners of complex lunch ->" << endl << endl;
    while (!queue_copy.empty())
    {
        cout << queue_copy.front().get_name() + " " + queue_copy.front().get_surname() + " , balance: " <<  queue_copy.front().get_money() << endl;
        queue_copy.pop();
    }  
    cout << "Now, let us give them month grand which is 3100 tugrics, using <map> function"<< endl;
    auto give_everybody_grand = [](Student student){
        student.add_money(3100);
        return Student(student);
    };
    queue.map(give_everybody_grand);

    cout <<endl << "Lucky owners of complex lunch NOW->" << endl <<endl;
    while (!queue.empty())
    {
        cout << queue.front().get_name() + " " + queue.front().get_surname() + " , balance: " <<  queue.front().get_money() << endl;
        queue.pop();
    }  


} 


int main(){
    Menu menu;
    MenuElement main_menu_element_list[]={
        MenuElement("Start tests", new StartTestCommand()),
        MenuElement("Run initialization dialog", new StartDialogCommand()),
        MenuElement("Run map where reduce showcase", new RunFunctionCommand(show_map_where_reduce_example))
    };
    menu.add_menu_element(main_menu_element_list[0]);
    menu.add_menu_element(main_menu_element_list[1]);
    menu.add_menu_element(main_menu_element_list[2]);
    menu.exec();
    
}