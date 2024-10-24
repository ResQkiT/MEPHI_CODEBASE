#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string
#include <vector>
#include <iostream>  // for std::stoi, std::stod
#include <sstream> 
#include <cstring> // для функции strcmp

#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                 // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"                     // for Ref


#include "LinkedList.hpp"  // Предположим, что у вас есть реализация LinkedList
#include "tests.h"

using namespace ftxui;

// Базовый абстрактный класс для работы со списком
class IListManager {
public:
    virtual void push_back(const std::string& value) = 0;
    virtual void push_front(const std::string& value) = 0;
    virtual void insert_at(const std::string& value, size_t index) = 0;
    virtual std::string get(size_t index) = 0;
    virtual size_t get_size() = 0;
    virtual void output(std::string& output) = 0;
    virtual ~IListManager() = default;
};

// Шаблонный класс, который управляет списком для каждого типа
template <typename T>
class ListManager : public IListManager {
    LinkedList<T> list;
public:
    // Добавить в конец
    void push_back(const std::string& value) override {
        if constexpr (std::is_same_v<T, int>) {
            list.push_back(std::stoi(value));
        } else if constexpr (std::is_same_v<T, double>) {
            list.push_back(std::stod(value));
        } else if constexpr (std::is_same_v<T, float>) {
            list.push_back(std::stof(value));
        } else if constexpr (std::is_same_v<T, std::string>) {
            list.push_back(value);
        }
    }

    // Добавить в начало
    void push_front(const std::string& value) override {
        if constexpr (std::is_same_v<T, int>) {
            list.push_front(std::stoi(value));
        } else if constexpr (std::is_same_v<T, double>) {
            list.push_front(std::stod(value));
        } else if constexpr (std::is_same_v<T, float>) {
            list.push_front(std::stof(value));
        } else if constexpr (std::is_same_v<T, std::string>) {
            list.push_front(value);
        }
    }

    // Вставить элемент по индексу
    void insert_at(const std::string& value, size_t index) override {
        if constexpr (std::is_same_v<T, int>) {
            list.insert_at(std::stoi(value), index);
        } else if constexpr (std::is_same_v<T, double>) {
            list.insert_at(std::stod(value), index);
        } else if constexpr (std::is_same_v<T, float>) {
            list.insert_at(std::stof(value), index);
        } else if constexpr (std::is_same_v<T, std::string>) {
            list.insert_at(value, index);
        }
    }

    // Получить элемент по индексу
    std::string get(size_t index) override {
        if (index >= list.size()) {
            return "Index out of bounds";
        }

        if constexpr (std::is_same_v<T, std::string>) {
            return list.get(index);
        } else {
            return std::to_string(list.get(index));
        }
    }

    // Вывод списка
    void output(std::string& output) override {
        output = "";
        for (size_t i = 0; i < list.size(); i++) {
            if constexpr (std::is_same_v<T, std::string>) {
                output += list.get(i) + "->";
            } else {
                output += std::to_string(list.get(i)) + "->";
            }
        }
    }

    size_t get_size() override{
        return list.size();
    }
};

int main(int argc, char* argv[]) {

    if (argc == 2 && strcmp(argv[1], "-t") == 0) { // сравнение строк
        run_tests(std::cout);
        return 0;
    } 
    std::string enter = "";
    auto enter_label = Input(&enter);  // Поле ввода

    std::string index_enter = "";      // Поле для индекса
    auto index_label = Input(&index_enter);  // Поле для индекса

    bool show_index_input = false;  // Управляет отображением поля ввода индекса

    std::string output;  // Поле для вывода

    auto screen = ScreenInteractive::TerminalOutput();

    // Список типов данных для выбора
    std::vector<std::string> type_list = {
        "int",
        "string",
        "double",
        "float",
    };
    int selected = 0;
    int prev_selected = -1;  // Сохраняем предыдущее значение выбранного типа

    // Указатель на текущий менеджер списка
    std::unique_ptr<IListManager> list_manager;

    // Функция для создания менеджера списка в зависимости от типа
    auto create_list_manager = [&]() {
        if (type_list[selected] == "int") {
            list_manager = std::make_unique<ListManager<int>>();
        } else if (type_list[selected] == "string") {
            list_manager = std::make_unique<ListManager<std::string>>();
        } else if (type_list[selected] == "double") {
            list_manager = std::make_unique<ListManager<double>>();
        } else if (type_list[selected] == "float") {
            list_manager = std::make_unique<ListManager<float>>();
        }
        output = "ListManager updated to " + type_list[selected]; // Обновляем текст после переключения
    };

    // Создать менеджер для начального выбранного типа
    create_list_manager();

    // Действие при нажатии на кнопку Append
    auto push_back_in_list_action = [&]() {
        if (list_manager) {
            list_manager->push_back(enter);
            enter = "";  // Очистить поле ввода после добавления
        }
    };

    // Действие при нажатии на кнопку Prepend
    auto push_front_in_list_action = [&]() {
        if (list_manager) {
            list_manager->push_front(enter);
            enter = "";  // Очистить поле ввода после добавления
        }
    };

    // Действие при вставке элемента по индексу
    auto insert_at_element_action = [&]() {
        if (list_manager && !enter.empty() && !index_enter.empty()) {
            size_t index = std::stoi(index_enter);
            list_manager->insert_at(enter, index);
            enter = "";  // Очистить поля ввода
            index_enter = "";
            show_index_input = false;  // Скрыть поле для индекса
        }
    };

    // Действие при нажатии на кнопку Get
    auto get_element_action = [&]() {
        output = "";
        if (!index_enter.empty()) {
            size_t index = std::stoi(index_enter);
            output = list_manager->get(index);  // Получить элемент по индексу
            index_enter = "";  // Очистить поле ввода после получения
        }
    };

    // Действие при нажатии на кнопку Print
    auto write_list = [&]() {
        if (list_manager) {
            list_manager->output(output);
        }
    };

    // Проверка на изменение типа
    auto check_type_change = [&]() {
        if (prev_selected != selected) {
            prev_selected = selected;
            create_list_manager();  // Пересоздаем менеджер для нового типа
        }
    };

    auto get_first_action = [&](){
        output = "";
        if (list_manager) {
            size_t index = 0;
            output ="First element in list: " + list_manager->get(index);  // Получить элемент по индексу
            index_enter = "";  // Очистить поле ввода после получения
        }
    };

    auto get_last_action = [&](){
        output = "";
        if (list_manager) {
            size_t index = list_manager->get_size() - 1;
            output ="First element in list: " + list_manager->get(index);  // Получить элемент по индексу
            index_enter = "";  // Очистить поле ввода после получения
        }
    };

    auto get_size_action = [&](){
        output = "";
        if(list_manager){
            output ="Size of current list: " + std::to_string(list_manager->get_size());
        }
    };

    auto run_test_action = [&](){
        std::ostringstream os;
        run_tests(os);
        output = os.str();
    };
    // Кнопка выхода
    auto exit_button = Button("exit", [&] { screen.Exit(); }, ButtonOption::Ascii()) | align_right;

    // Объединение всех компонентов интерфейса
    auto all_container = Container::Vertical({
        Container::Horizontal({
            Renderer([] { return paragraphAlignLeft("Лабораторная работа 1 Сафронов Илья Б23 - 554"); }) | border | size(WIDTH, EQUAL, 25),
            Renderer([] { return text(""); }) | flex,
            exit_button | align_right | border,
        }),
        Container::Horizontal({
            Toggle(&type_list, &selected) | borderRounded,  // Переключатель типа
            Container::Horizontal({
                Renderer([] { return text("input->"); }),
                enter_label,
                Renderer([]{return text("index->"); }),
                index_label   // Поле для ввода индекса показывается при необходимости
            }) | borderDashed | size(WIDTH, EQUAL, 50)
        }),
        Container::Vertical({
            Container::Horizontal({
                Button("Append", push_back_in_list_action, ButtonOption::Simple()) | flex,
                Button("Prepend", push_front_in_list_action, ButtonOption::Simple()) | flex,
                Button("Insert at index", insert_at_element_action, ButtonOption::Simple()) | flex,
                Button("Get", get_element_action, ButtonOption::Simple()) | flex,
            }),
            Container::Horizontal({
                Button("GetFirst", get_first_action, ButtonOption::Simple()) | flex,
                Button("GetLast", get_last_action, ButtonOption::Simple()) | flex,
                Button("GetSize", get_size_action, ButtonOption::Simple()) | flex,
                Button("Print", write_list, ButtonOption::Simple()) | flex,
                Button("Run tests", run_test_action, ButtonOption::Simple()) | flex
            }),
        }),
        Renderer([] { return separator(); }),

        Renderer([&] {
            check_type_change();  // Проверяем изменение типа перед каждым обновлением экрана
            return vbox(filler() , vbox({
                hflow(paragraphAlignCenter(output)) | size(HEIGHT, GREATER_THAN, 25) | border   // Параграф внизу
            }));
        }) 
    });

    screen.Loop(all_container);
}
