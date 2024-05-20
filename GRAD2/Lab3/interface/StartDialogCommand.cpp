#include <iostream>
#include "StartDialogCommand.h"
#include "../../ExtendedMenu/readio.h"
#include "../ActionHandler.h"

#include "../adapters/AbstractAdapter.h"
#include "../adapters/QueueAdapter.h"
#include "../adapters/DequeAdapter.h"
#include "../adapters/StackAdapter.h"
#include "../adapters/SegmentedDequeAdapter.h"

StartDialogCommand::StartDialogCommand(){}

StartDialogCommand::~StartDialogCommand(){};

template<class T>
void run(ActionHandler<T> & handler){
    char working_choose;

    bool is_running = true;
    cout << "Handler " + handler.get_type() + " is running\n";
    while (is_running)
    {
        cout << "Choose command: \n1 - create data sequence\n2 - show data sequence\n3 - append\n4 - prepend \n q - for exit\n";
        console_get_or_throw(working_choose);
        if(working_choose == '1'){
            handler.input_data();
        }else if(working_choose == '2'){
            handler.output_data();
        }else if(working_choose == '3'){
            handler.append_element();
        }else if(working_choose == '4'){
            handler.prepend_element();
        }else if(working_choose = 'q'){
            is_running = false;
        }
    }
}
template<class T> 
void set_adapter(ActionHandler<T> & handler){
    char adapter_choose;
    cout << "1 - stack \n2 - deque\n3 - queue\n4 - segmented deque\n";
    console_get_or_throw(adapter_choose);
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
void StartDialogCommand::exec(){
    char type_choose;
    bool is_running = true;
    while(is_running){
        std::cout << "1 - int\n 2 - double\n 3 - char \n 4 - string\n q - exit\n m - show map/where/reduce example\n"<<endl;
        console_get_or_throw(type_choose);
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