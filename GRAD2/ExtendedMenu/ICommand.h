#pragma once

//realization of command pattern
class ICommand{ 
public:
    virtual ~ICommand() = default;
    virtual void exec() = 0;
    virtual ICommand * clone() = 0;
};