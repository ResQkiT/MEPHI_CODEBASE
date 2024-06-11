#include <iostream>
#include "test.h"
#include "../ExtendedMenu/Menu.h"
#include "../ExtendedMenu/ICommand.h"
#include "../ExtendedMenu/MultiCommand.h"

#include "interface/StartTestCommand.h"
#include "interface/StartDialogCommand.h"
#include "interface/StressTestCommand.h"

int main(){

    Menu menu;
    MultiCommand<StartTestCommand> start_tests;
    MultiCommand<StartDialogCommand> start_dialog;
    MultiCommand<StressTestCommand> stress_test;
    MenuElement main_menu_element_list[]={
        MenuElement("Start tests", &start_tests),
        MenuElement("Start work", &start_dialog),
        MenuElement("Stress test", &stress_test)
    };

    menu.add_menu_element(main_menu_element_list, 3);

    menu.exec();

}