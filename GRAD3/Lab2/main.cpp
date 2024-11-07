#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <functional>
#include <filesystem>

#include "../../GRAD2/Lab2/DynamicArray.h"
#include "sorters/BubbleSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/CountingSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"
#include "tests.h"
#include "DataGenerator.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace std;
using namespace ftxui;


void update_file_list(std::vector<std::string> &files) {
    files.clear();
    for (const auto& entry : std::filesystem::directory_iterator("static")) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        run_tests(std::cout);
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "-g") == 0)
    {
        DataGenerator generator;
        generator.generate_random_data_file("data.txt", 1000, 0, 1000);
        return 0;
    }
    
    auto screen = ScreenInteractive::TerminalOutput();

    // Переменные для интерфейса
    std::vector<int> array;
    std::string array_input;
    int selected_sorter = 0;
    int selected_order = 0;
    std::string result;
    std::string filename_input;
    std::string sequence_size = "100"; // Размер последовательности по умолчанию
    std::vector<std::string> files;
    int selected_file = 0;


    DataGenerator data_generator;

    


    // Компоненты интерфейса
    auto array_input_component = Input(&array_input, "Введите числа через пробел");
    auto result_component = Renderer([&]
                                     { return text(result); });

    std::vector<std::string> sorters = {"BubbleSorter", "InsertionSorter", "CountingSorter", "MergeSorter", "QuickSorter"};
    auto sorter_selector = Radiobox(&sorters, &selected_sorter);

    std::vector<std::string> orders = {"Ascending", "Descending"};
    auto order_selector = Radiobox(&orders, &selected_order);

    auto filename_input_component = Input(&filename_input, "Введите имя файла");
    auto sequence_size_input_component = Input(&sequence_size, "Введите размер последовательности");

    auto generate_button = Button("Сгенерировать последовательность", [&]
                                  {
        if (!filename_input.empty()) {
            data_generator.generate_random_data_file(filename_input + ".txt", std::stoi(sequence_size), 0, 100);
            result = "Файл " + filename_input + " успешно создан.";
            update_file_list(files);
        } else {
            result = "Введите имя файла.";
        } 

    });

    auto file_selector = Radiobox(&files, &selected_file);

    auto load_button = Button("Загрузить последовательность", [&] {
        if (!files.empty()) {
            std::ifstream file("static/" + files[selected_file]);
            array.clear();
            int num;
            while (file >> num) {
                array.push_back(num);
            }
            result = "Файл " + files[selected_file] + " загружен.";
        } else {
            result = "Нет доступных файлов.";
        }
    });

    auto sort_button = Button("Сортировать", [&]
                              {
        if (array.empty()) {
            std::istringstream iss(array_input);
            int num;
            while (iss >> num) {
                array.push_back(num);
            }
        }

        // Выбор сортировщика
        std::unique_ptr<ISorter<int>> sorter;
        if (sorters[selected_sorter] == "BubbleSorter") {
            sorter = std::make_unique<BubbleSorter<int>>();
        } else if (sorters[selected_sorter] == "InsertionSorter") {
            sorter = std::make_unique<InsertionSorter<int>>();
        } else if (sorters[selected_sorter] == "CountingSorter") {
            sorter = std::make_unique<CountingSorter<int>>();
        } else if (sorters[selected_sorter] == "MergeSorter") {
            sorter = std::make_unique<MergeSorter<int>>();
        } else if (sorters[selected_sorter] == "QuickSorter") {
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

    auto exit_button = Button("Выход", [&]
                              { screen.ExitLoopClosure()(); });

    auto component = Container::Vertical({
        array_input_component,
        sorter_selector,
        order_selector,
        filename_input_component,
        sequence_size_input_component,
        generate_button,
        Renderer([&] { return text("Список файлов:"); }),
        file_selector,
        load_button,
        sort_button,
        result_component,
        exit_button
    });

    auto renderer = Renderer(component, [&]
                             { return vbox({text("Сортировщик") | bold,
                                            array_input_component->Render(),
                                            text("Выберите сортировщик:"),
                                            sorter_selector->Render(),
                                            separator(),
                                            text("Выберите порядок сортировки:"),
                                            order_selector->Render(),
                                            separator(),
                                            text("Введите имя файла для генерации последовательности:"),
                                            filename_input_component->Render(),
                                            text("Введите размер последовательности:"),
                                            sequence_size_input_component->Render(),
                                            generate_button->Render(),
                                            text("Список файлов:"),
                                            file_selector->Render(),
                                            load_button->Render(),
                                            sort_button->Render(),
                                            separator(),
                                            text("Результат:"),
                                            result_component->Render(),
                                            separator(),
                                            exit_button->Render()}) |
                                      border; });

    update_file_list(files);
    screen.Loop(renderer);
    return 0;
}