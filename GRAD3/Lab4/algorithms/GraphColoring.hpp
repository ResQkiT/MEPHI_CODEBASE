#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <set>

#include "IExecutable.hpp"

template <class T>
class Graph;

template <class T>
class GraphColoring : public IExecutable<T> {
private:
    std::vector<std::string> _used_colors;

    std::vector<std::shared_ptr<Vertex<T>>> _queue; // initially holds all vertices sorted by degree

public:

    std::vector<std::string> color_names = {
        "red", "green", "blue", "yellow", "purple",
        "orange", "pink", "brown", "black", "white",
        "gray", "cyan", "magenta", "lime", "teal",
        "navy", "maroon", "olive", "gold", "violet"
    };

    virtual ~GraphColoring() = default;

    virtual void execute(Graph<T>& graph) {

        _queue.clear();
        for (const auto& v_name : graph._vertices_names) {
            auto vertex = graph._vertices[v_name];
            _queue.push_back(vertex);
        }
        std::sort(_queue.begin(), _queue.end(), [&](std::shared_ptr<Vertex<T>> a, std::shared_ptr<Vertex<T>> b) {
            return a->get_input_edges().size() + a->get_output_edges().size() >
                   b->get_input_edges().size() + b->get_output_edges().size();
        });

        std::map<std::string, std::string> vertex_colors;

        for (auto vertex : _queue) {
            std::set<std::string> used_colors;
            auto neighbors = vertex->get_neighbors();
            for (auto neighbor : neighbors) {
                if (!vertex_colors.empty() && vertex_colors.find(neighbor->get_name()) != vertex_colors.end()) {
                    used_colors.insert(vertex_colors[neighbor->get_name()]);
                }
            }

            for (auto color : color_names) {
                if (used_colors.find(color) == used_colors.end()) {
                    vertex_colors[vertex->get_name()] = color;
                    break;
                }
            }
        }

        for (const auto& pair : vertex_colors) {
            auto vertex = graph._vertices[pair.first];
            vertex->set_color(pair.second);
        }
    }

    virtual std::string getResult() const {
        return "finish work correct";
    }
};