#include <iostream>
#include "test.h"
#include "interface/StartTestCommand.h"
#include "../ExtendedMenu/Menu.h"
#include "../ExtendedMenu/ICommand.h"
#include "../ExtendedMenu/MultiCommand.h"

int main(){
    Menu menu;
    MultiCommand<StartTestCommand> command;
    MenuElement main_menu_element_list[]={
        MenuElement("Start tests", &command)
    };

    menu.add_menu_element(main_menu_element_list, 1);

    menu.exec();

}