#pragma once
#include <type_traits>
#include "ICommand.h"

template <class _command_type>
requires std::is_base_of<ICommand, _command_type>::value
class MultiCommand : public ICommand{
private:
    _command_type command;
public:
    MultiCommand() = default;
    void exec() override {
        command.exec();
    }
    MultiCommand<_command_type> * clone(){
        return new MultiCommand<_command_type>();
    }
};