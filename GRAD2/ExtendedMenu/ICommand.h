#pragma once

//realization of command pattern
class ICommand{ 
public:
    virtual ~ICommand();
    virtual void exec() = 0;
    virtual ICommand * clone() = 0;
};