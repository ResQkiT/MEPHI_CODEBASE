#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <functional>

#include "../../GRAD2/Lab2/DynamicArray.h"
#include "sorters/BubbleSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"
#include "tests.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace std;
using namespace ftxui;

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "-t") == 0) {
        run_tests(std::cout);
        return 0;
    }

    auto screen = ScreenInteractive::TerminalOutput();

    // Переменные для интерфейса
    std::vector<int> array;
    std::string array_input;
    int selected_sorter = 0;
    int selected_order = 0;
    std::string result;

    // Компоненты интерфейса
    auto array_input_component = Input(&array_input, "Введите числа через пробел");
    auto result_component = Renderer([&] {
        return text(result);
    });

    std::vector<std::string> sorters = {"BubbleSorter", "InsertionSorter", "CountingSorter", "MergeSorter", "QuickSorter"};
    auto sorter_selector = Radiobox(&sorters, &selected_sorter);
    
    std::vector<std::string> orders = {"Ascending", "Descending"};
    auto order_selector = Radiobox(&orders, &selected_order);

    auto sort_button = Button("Сортировать", [&] {
        // Преобразование строки в массив чисел
        array.clear();
        std::istringstream iss(array_input);
        int num;
        while (iss >> num) {
            array.push_back(num);
        }

        // Выбор сортировщика
        std::unique_ptr<ISorter<int>> sorter;
        if (selected_sorter == 0) {
            sorter = std::make_unique<BubbleSorter<int>>();
        } else if (selected_sorter == 1) {
            sorter = std::make_unique<InsertionSorter<int>>();
        } else if (selected_sorter == 2) {
            sorter = std::make_unique<CountingSorter<int>>();
        } else if (selected_sorter == 3) {
            sorter = std::make_unique<MergeSorter<int>>();
        } else if (selected_sorter == 4) {
            sorter = std::make_unique<QuickSorter<int>>();
        }

        // Сортировка массива
        DynamicArray<int> dynamic_array(array.size());
        for (size_t i = 0; i < array.size(); ++i) {
            dynamic_array[i] = array[i];
        }

        // Выбор порядка сортировки
        if (selected_order == 0) {
            sorter->sort(dynamic_array.begin(), dynamic_array.end(), std::less<int>());
        } else {
            sorter->sort(dynamic_array.begin(), dynamic_array.end(), std::greater<int>());
        }

        // Преобразование результата в строку
        result.clear();
        for (const auto& elem : dynamic_array) {
            result += std::to_string(elem) + " ";
        }
    });

    auto exit_button = Button("Выход", screen.ExitLoopClosure());

    auto component = Container::Vertical({
        array_input_component,
        sorter_selector,
        order_selector,
        sort_button,
        result_component,
        exit_button
    });

    auto renderer = Renderer(component, [&] {
        return vbox({
            text("Сортировщик") | bold,
            array_input_component->Render(),
            text("Выберите сортировщик:"),
            sorter_selector->Render(),
            text("Выберите порядок сортировки:"),
            order_selector->Render(),
            sort_button->Render(),
            text("Результат:"),
            result_component->Render(),
            exit_button->Render()
        }) | border;
    });

    screen.Loop(renderer);
    return 0;
}