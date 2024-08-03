#include <iostream>
#include <string>
#include "../ExtendedMenu/readio.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "DynamicArraySequence.h"
#include "ImmutableDynamicArraySequence.h"
#include "ImmutableLinkedListSequense.h"
#include "LinkedListSequence.h"
#include "AbstractActionListener.h"
#include "MutableActionHandler.h"
#include "ImmutableActionHandler.h"

#include "test.h"

enum class modes{  STARTING,
                    RUNNING,
                    ENDING};

enum class access_mode{MUTABLE, IMMUTABLE};
enum class type_mode {INT, DOUBLE, CHAR, STRING};

using namespace std;


template<class T>
void work(AbstractActionListener<T> * listener){
    bool is_working = true;
    while(is_working){
        cout << "   choose command\n    1 - for create new list\n\\
        2 - for showing list\n\\
        3 - for extract and show subsequence\n\\
        4 - for adding element at the end\n\\
        5 - for adding element at definite possition\n\\
        6 - for adding element at begining\n\\
        7 - create another list and concat with yours\n\\
        -1 - for return back\n->";
        int choice;
        console_get_or_throw(choice);
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
        case 7:
            listener->concat_with_new_sequence();
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
    cout << "Lets create first data structure!: " << endl;
    modes mode = modes::RUNNING;
    cout << "Start tests?(y/n)" << endl;
    char t;
    cin >> t;
    if(t == 'y')
        run_tests();
        
    int mutable_choice;
    int type_choice;
    while (mode == modes::RUNNING)
    {    
        cout << "1 - to work with mutable structures \n2 - to work with immutable structures \n->";
        console_get_or_throw(mutable_choice);
        
        cout <<"Choose type: 1 - int, 2 - double, 3 - char, 4 - string\n->";
        console_get_or_throw(type_choice);

        if(mutable_choice == 1){
            if(type_choice == 1){
                AbstractActionListener<int> * listener = new MutableActionHandler<int>(); 
                work(listener);
            }else if (type_choice == 2)
            {
                AbstractActionListener<double> * listener = new MutableActionHandler<double>(); 
                work(listener);
            }
            else if (type_choice == 3)
            {
                AbstractActionListener<char> * listener = new MutableActionHandler<char>(); 
                work(listener);
            }
            else if (type_choice == 4)
            {
                AbstractActionListener<string> * listener = new MutableActionHandler<string>(); 
                work(listener);
            }
            else if (type_choice == -1)
            {
                continue;
            }
        }else if(mutable_choice == 2){
            if(type_choice == 1){
                AbstractActionListener<int> * listener = new ImmutableActionHandler<int>(); 
                work(listener);
            }else if (type_choice == 2)
            {
                AbstractActionListener<double> * listener = new ImmutableActionHandler<double>(); 
                work(listener);
            }
            else if (type_choice == 3)
            {
                AbstractActionListener<char> * listener = new ImmutableActionHandler<char>(); 
                work(listener);
            }
            else if (type_choice == 4)
            {
                AbstractActionListener<string> * listener = new ImmutableActionHandler<string>(); 
                work(listener);
            }
            else if (type_choice == -1)
            {
                continue;
            }
        }else{
            break;
        }
    }
    return 0;
}