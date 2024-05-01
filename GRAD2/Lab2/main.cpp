#include <iostream>
#include <string>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "DynamicArraySequence.h"
#include "ImmutableDynamicArraySequence.h"
#include "ImmutableLinkedListSequense.h"
#include "LinkedListSequence.h"
#include "readio.h"
#include "tests.h"
#include "AbstractActionListener.h"
#include "MutableActionHandler.h"



enum class modes{   MUTABLE,
                    IMMUTABLE,
                    STARTING,
                    RUNNING,
                    ENDING};

enum class access_mode{MUTABLE, IMMUTABLE};
enum class type_mode {INT, DOUBLE, CHAR, STRING};

using namespace std;

void runtest(){
    using namespace tests;
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    test18();
    test19();
    test20();
    std::cout << "ALL TEST PASSED!" << std::endl;
}

template<class T>
void work(AbstractActionListener<T> * listener){
    //тут уже определен тип для работы.
    bool is_working = true;
    while(is_working){
        cout << "   choose command\n    1 - for create new list\n\\
        2 - for showing list\n\\
        3 - for extract and show subsequence\n\\
        4 - for adding element at the end\n\\
        5 - for adding element at definite possition\n\\
        6 - for adding elememnt at begining\n\\
        -1 - for return back\n->";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            listener->create_sequence_dialog();
            break;
        case 2:
            listener->print_working_sequence();
            break;
        case 3:
            listener->get_n_show_subsequence();
            break;
        case 4:
            listener->add_element_to_end();
            break;
        case 5:
            listener->add_element_to_position();
            break;
        case 6:
            listener->add_element_to_begin();
            break;
        
        case -1:
            is_working = false;
            break;
        default:
            is_working = false;
            break;
        }
    }
}

int main()
{  
    runtest();
    cout << "Lets create first data structure!: " << endl;

    modes mode = modes::RUNNING;

    int mutable_choice;
    int type_choice;
    //main program loop
    while (mode == modes::RUNNING)
    {    
        
        cout << "1 - to work with mutable structures \n2 - to work with immutable structures \n-1 for exit\n->";
        cin >> mutable_choice;
        cout << "Choose type: 1 - int, 2 - double, 3 - char, 4 - string\n->";
        cin >> type_choice;
        if(type_choice == 1){
            AbstractActionListener<int> * listener1 = new MutableActionHandler<int>(); 
            work(listener1);
        }else if (type_choice == 2)
        {
            AbstractActionListener<double> * listener1 = new MutableActionHandler<double>(); 
            work(listener1);
        }
        else if (type_choice == 3)
        {
            AbstractActionListener<char> * listener1 = new MutableActionHandler<char>(); 
            work(listener1);
        }
        else if (type_choice == 4)
        {
            AbstractActionListener<string> * listener1 = new MutableActionHandler<string>(); 
            work(listener1);
        }
        else if (type_choice == -1)
        {
            mode = modes::ENDING;
        }
    }
    return 0;
}