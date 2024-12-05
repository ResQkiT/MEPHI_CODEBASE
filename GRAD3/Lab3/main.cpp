#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <filesystem>
#include <fstream>
#include <deque>
#include <array>
#include <map>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "HashMap.hpp"
#include "test.h"
#include "DBAdapter.hpp"
#include "Query.hpp"
#include <cstring>
#include "ExecutionTimeMeasurer.hpp"
#include "CachedDBAdapter.hpp"

using namespace std;
using namespace ftxui;

struct Record {
    int age;
    std::string name;
    Record(const std::string& line) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            age = std::stoi(line.substr(0, commaPos));
            name = line.substr(commaPos + 1);
        } else {
            throw std::invalid_argument("Invalid record format.");
        }
    }
};

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
        run_test();
        return 0;
    }

    auto screen = ScreenInteractive::TerminalOutput();

    int selected_adapter = 0;
    int selected_query = 0;
    std::deque<std::string> displayed_results;
    std::vector<std::string> all_results;
    std::vector<std::string> files;
    std::string save_filename;
    std::string new_query_name;

    std::unique_ptr<DBAdapter<Record>> dbAdapter = std::make_unique<DBAdapter<Record>>("../test_data/data.txt");
    std::unique_ptr<CachedDBAdapter<Record>> cachedAdapter = std::make_unique<CachedDBAdapter<Record>>("../test_data/data.txt", 10);

    auto new_query_name_component = Input(&new_query_name, "Enter query name");
    auto result_component = Renderer([&] {
        std::string result;
        for (const auto& line : displayed_results) {
            result += line + "\n";
        }
        return text(result);
    });
    auto save_filename_component = Input(&save_filename, "Enter filename to save results");

    std::vector<std::string> adapters = {"DBAdapter", "CachedDBAdapter"};
    auto adapter_selector = Radiobox(&adapters, &selected_adapter);

    std::map<std::string, std::function<void(Query<Record>&)>> saved_queries;
    std::vector<std::string> query_names;
    auto query_menu = Menu(&query_names, &selected_query);

    std::vector<std::string> conditions = {
        "Name starts with A",
        "Age greater than 50",
        "Age less than 18",
        "Age between 18 and 50"
    };
    std::array<bool, 4> conditions_selected;
    auto conditions_checkboxes = Container::Vertical({});
    for (size_t i = 0; i < conditions.size(); ++i) {
        conditions_selected[i] = false; 
        conditions_checkboxes->Add(Checkbox(conditions[i], &conditions_selected[i]));
    }

    auto save_query_button = Button("Save Query", [&] {
        if (!new_query_name.empty()) {
            saved_queries[new_query_name] = [conditions_selected](Query<Record>& query) {
                if (conditions_selected[0]) {
                    query.add_condition([](const Record& x) { return x.name[0] == 'A'; });
                }
                if (conditions_selected[1]) {
                    query.add_condition([](const Record& x) { return x.age > 50; });
                }
                if (conditions_selected[2]) {
                    query.add_condition([](const Record& x) { return x.age < 18; });
                }
                if (conditions_selected[3]) {
                    query.add_condition([](const Record& x) { return x.age > 18 && x.age <= 50; });
                }
            };
            query_names.push_back(new_query_name);
            new_query_name.clear();
            fill(conditions_selected.begin(), conditions_selected.end(), false);
        }
    });

    auto execute_button = Button("Execute Query", [&] {
        if (selected_query < query_names.size()) {
            Query<Record> query(query_names[selected_query]);
            displayed_results.clear();
            all_results.clear();

            if (saved_queries.find(query_names[selected_query]) != saved_queries.end()) {
                saved_queries[query_names[selected_query]](query);
            }

            std::vector<Record> results;
            if (selected_adapter == 0) {
                results = dbAdapter->find(query);
            } else {
                results = cachedAdapter->find(query);
            }

            for (const auto& record : results) {
                std::string line = "Age: " + std::to_string(record.age) + ", Name: " + record.name;
                all_results.push_back(line);
                if (displayed_results.size() < 5) {
                    displayed_results.push_back(line);
                }
            }
        }
    });

    auto save_button = Button("Save Results", [&] {
        if (!save_filename.empty()) {
            std::ofstream outfile(save_filename);
            if (outfile.is_open()) {
                for (const auto& line : all_results) {
                    outfile << line << "\n";
                }
                outfile.close();
                displayed_results.push_back("Results saved to " + save_filename);
                if (displayed_results.size() > 5) {
                    displayed_results.pop_front();
                }
            } else {
                displayed_results.push_back("Failed to open file " + save_filename);
                if (displayed_results.size() > 5) {
                    displayed_results.pop_front();
                }
            }
        } else {
            displayed_results.push_back("Please enter a filename to save results.");
            if (displayed_results.size() > 5) {
                displayed_results.pop_front();
            }
        }
    });

    auto exit_button = Button("Exit", [&] { screen.ExitLoopClosure()(); });

    auto component = Container::Vertical({
        new_query_name_component,
        conditions_checkboxes,
        save_query_button,
        adapter_selector,
        query_menu,
        execute_button,
        save_filename_component,
        save_button,
        result_component,
        exit_button
    });

    auto renderer = Renderer(component, [&] {
        return vbox({
            text("Database Query Interface") | bold,
            text("Enter Query Name:"),
            new_query_name_component->Render(),
            text("Select Conditions:"),
            conditions_checkboxes->Render(),
            save_query_button->Render(),
            text("Select Adapter Type:"),
            adapter_selector->Render(),
            text("Select Query:"),
            query_menu->Render(),
            execute_button->Render(),
            separator(),
            text("Results:"),
            result_component->Render() | size(HEIGHT, EQUAL, 5),
            separator(),
            text("Enter Filename to Save Results:"),
            save_filename_component->Render(),
            save_button->Render(),
            separator(),
            exit_button->Render()
        }) | border;
    });

    screen.Loop(renderer);
    return 0;
}