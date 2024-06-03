#pragma once
#include "../../ExtendedMenu/ICommand.h"
#include "../test.h"

class StartTestCommand : public ICommand
{
public:
    StartTestCommand();
    ~StartTestCommand();
    void exec() override;
    StartTestCommand * clone() override;
};

