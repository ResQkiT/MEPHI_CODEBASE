#include <iostream>
#include "StartDialogCommand.h"
#include "../../ExtendedMenu/readio.h"
#include "SetAdapter.h"
#include "AbstractAdapter.h"
#include "TreeAdapter.h"
#include "ActionHandler.h"

StartDialogCommand::StartDialogCommand(){}

StartDialogCommand::~StartDialogCommand(){};

template<class T>
void run(ActionHandler<T> & handler){
    char working_choose;

    bool is_running = true;
    cout << "Handler " + handler.get_type() + " is running\n";
    while (is_running)
    {
        cout << "Choose command: \n1 - create data sequence\n2 -'pre-order'\n3 - 'in-order'\n4 - 'post-order'\n5 - insert\n6 - remove\n7 - find\n q - exit\n";
        console_get_or_throw(working_choose);
        if(working_choose == '1'){
            handler.input_data();
        }else if(working_choose == '2'){
            handler.pre_order_output_data();
        }else if(working_choose == '3'){
            handler.in_order_output_data();
        }else if(working_choose == '4'){
            handler.post_order_output_data();
        }else if(working_choose == '5'){
            handler.insert_element();
        }else if(working_choose == '6'){
            handler.remove_element();
        }else if(working_choose == '7'){
            handler.find_element();
        }else if(working_choose == 'q'){
            is_running = false;
        }
    }
}
template<class T> 
void set_adapter(ActionHandler<T> & handler){
    AbstractAdapter<T> * adapter;
    bool is_choice_ok;  
    do{
        is_choice_ok = true;
        cout << "1 - simple search tree \n2 - AVL search tree\n3 - Set\n";
        char adapter_choose ;
        console_get_or_throw(adapter_choose);
        if (adapter_choose == '1'){
            adapter = new TreeAdapter<T, BinaryTree>();
        }else if(adapter_choose == '2'){
            adapter = new TreeAdapter<T, AvlTree>();
        }else if(adapter_choose == '3'){
            adapter = new SetAdapter<T>();
        }else{
            is_choice_ok = false;
        }
    }while (!is_choice_ok);

    cout << adapter->get_type() << endl;
    handler.set_adapter(adapter);
    delete adapter;
}
void StartDialogCommand::exec(){
    char type_choose;
    bool is_running = true;
    while(is_running){
        std::cout << "1 - int\n 2 - long int\n 3 - char \n q - exit\n"<<endl;
        console_get_or_throw(type_choose);
        if (type_choose == '1'){
            ActionHandler<int> handler;
            set_adapter(handler);
            run(handler);
        }else if(type_choose == '2'){
            ActionHandler<long long> handler;
            set_adapter(handler);
            run(handler);
        }else if(type_choose == '3'){
            ActionHandler<char> handler;
            set_adapter(handler);
            run(handler);
        }else if(type_choose == 'q'){
            is_running = false;
        }else{
            continue;
        }
    }
}
StartDialogCommand * StartDialogCommand::clone(){
    return new StartDialogCommand();
}