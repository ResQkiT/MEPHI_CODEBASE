#include "StartTestCommand.h"

StartTestCommand::StartTestCommand()
{
}

StartTestCommand::~StartTestCommand() = default;

void StartTestCommand::exec(){
    start_tests();
}
StartTestCommand * StartTestCommand::clone(){
    return new StartTestCommand();
}