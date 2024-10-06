
#include <memory> // for allocator, __shared_ptr_access
#include <string> // for char_traits, operator+, string, basic_string

#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                 // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"                     // for Ref

using namespace ftxui;
int main()
{
    auto action = []{return 0;};
    std::vector<std::string> command_list = {
      "int",
      "string",
      "double",
      "float",
    };
    int selected = 0;
    auto screen = ScreenInteractive::TerminalOutput();

    auto exit_button = Button("exit", [&](){screen.Exit();}, ButtonOption::Ascii()) | align_right;

    auto all_container =Container::Vertical({
            Container::Horizontal({
                Renderer([]{return paragraphAlignLeft("Лабортаорная работа 1 Сафронов Илья Б23 - 554");}) | border,
                Renderer([]{return text("");}) | border | flex ,
                exit_button | align_right | border
            }),

            Renderer([]{ return separator(); }),
            Container::Vertical({
                Container::Horizontal({
                        Button("Append", action, ButtonOption::Ascii()) | flex | border,
                        Button("Prepend", action, ButtonOption::Ascii()) | flex | border,
                        Button("insert", action, ButtonOption::Ascii()) | flex | border,
                        Button("Get", action, ButtonOption::Ascii()) | flex | border
                }),
                Container::Horizontal({
                        Button("GetFirst", action, ButtonOption::Simple()) | flex,
                        Button("GetLast", action, ButtonOption::Simple()) | flex,
                        Button("GetSize", action, ButtonOption::Simple()) | flex,
                })
            }),
                Radiobox(&command_list, &selected)
            
        });

    
    screen.Loop(all_container);
}