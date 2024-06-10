#include <iostream>
#include "test.h"
#include "interface/StartTestCommand.h"
#include "../ExtendedMenu/Menu.h"
#include "../ExtendedMenu/ICommand.h"
#include "../ExtendedMenu/MultiCommand.h"
#include "interface/StartDialogCommand.h"

int main(){

    Menu menu;
    MultiCommand<StartTestCommand> start_tests;
    MultiCommand<StartDialogCommand> start_dialog;
    MenuElement main_menu_element_list[]={
        MenuElement("Start tests", &start_tests),
        MenuElement("Start work", &start_dialog),
    };

    menu.add_menu_element(main_menu_element_list, 2);

    menu.exec();

}