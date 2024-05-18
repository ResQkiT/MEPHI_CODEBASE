#pragma once
#include "../../ExtendedMenu/ICommand.h"

class StartDialogCommand : public ICommand{
public:
    StartDialogCommand();
    ~StartDialogCommand();
    void exec() override;
    StartDialogCommand * clone() override;
};