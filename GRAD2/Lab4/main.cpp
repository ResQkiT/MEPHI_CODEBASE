#include <iostream>
#include "test.h"
#include "interface/StartTestCommand.h"
#include "../ExtendedMenu/Menu.h"
#include "../ExtendedMenu/ICommand.h"
#include "../ExtendedMenu/MultiCommand.h"
#include "Property.h"

template<class T>
class Test{

public:
    Property<int> a;
    Test(): a{0} {};
};

int main(){
    Test<int> test;
    std::cout << test.a;
    test.a = 5;
    std::cout << test.a;

    Menu menu;
    MultiCommand<StartTestCommand> command;
    MenuElement main_menu_element_list[]={
        MenuElement("Start tests", &command)
    };

    menu.add_menu_element(main_menu_element_list, 1);

    menu.exec();

}