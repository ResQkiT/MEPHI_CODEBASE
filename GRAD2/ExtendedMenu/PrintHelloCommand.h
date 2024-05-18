#pragma once
#include "ICommand.h"

class PrintHelloCommand : public ICommand{
public:
    PrintHelloCommand();
    ~PrintHelloCommand() = default;
    void exec() override;
    PrintHelloCommand * clone() override;
};