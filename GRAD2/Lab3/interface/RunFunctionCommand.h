#pragma once
#include "../../ExtendedMenu/ICommand.h"
#include <functional>

class RunFunctionCommand : public ICommand{
private:
    std::function<void(void)> runtime_function;
public:

    RunFunctionCommand(std::function<void(void)> function);
    ~RunFunctionCommand();
    void exec() override;
    RunFunctionCommand * clone() override;
};