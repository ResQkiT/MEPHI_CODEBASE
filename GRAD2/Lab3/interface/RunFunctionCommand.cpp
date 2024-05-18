#include "RunFunctionCommand.h"
#include <functional>

RunFunctionCommand::RunFunctionCommand(std::function<void(void)> function){
    runtime_function = function;
}
RunFunctionCommand::~RunFunctionCommand() = default;
void RunFunctionCommand::exec(){
    runtime_function();
}
RunFunctionCommand * RunFunctionCommand::clone(){
    return new RunFunctionCommand(runtime_function);
}