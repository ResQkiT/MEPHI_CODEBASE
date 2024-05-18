#include "PrintHelloCommand.h"
#include <iostream>
PrintHelloCommand::PrintHelloCommand(){}
void PrintHelloCommand::exec(){
    std::cout << "Hello from hello command: "<< this << std::endl;
}
PrintHelloCommand * PrintHelloCommand::clone(){
    return new PrintHelloCommand();
}