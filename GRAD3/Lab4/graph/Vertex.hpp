#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Edge.hpp"

template<class T> 
class Edge;

template<class T>
class Vertex {
private:
    std::string _name;                                     
    T _data;                                               
    std::string _color;       

    std::vector<std::shared_ptr<Edge<T>>> _input_edges;     
    std::vector<std::shared_ptr<Edge<T>>> _output_edges;    

public:

    Vertex(T data) 
        : _name(""), _data(std::move(data)), _color("black") {}

    Vertex(const std::string& name) 
        : _name(name), _data(T()), _color("black") {}

    Vertex(const std::string& name, T data) 
        : _name(name), _data(std::move(data)), _color("black") {}

    Vertex(const std::string& name, T data, const std::string& color) 
        : _name(name), _data(std::move(data)), _color(color) {}

    Vertex(const Vertex<T>& vertex) = delete;               

    Vertex(Vertex<T>&& vertex) noexcept 
        : _name(std::move(vertex._name)),
        _data(std::move(vertex._data)),
        _color(std::move(vertex._color)),
        _input_edges(std::move(vertex._input_edges)),
        _output_edges(std::move(vertex._output_edges))
        {}

    Vertex<T>& operator=(const Vertex<T>& vertex) = delete; 

    Vertex<T>& operator=(Vertex<T>&& vertex) noexcept {
        if (this != &vertex) {
            _name = std::move(vertex._name);
            _data = std::move(vertex._data);
            _input_edges = std::move(vertex._input_edges);
            _output_edges = std::move(vertex._output_edges);
            _color = std::move(vertex._color);
        }
        return *this;
    }

    T get_data() const {
        return _data;
    }

    void set_data(const T& data) {
        _data = data;
    }

    const std::string& get_color() const {
        return _color;
    }

    void set_color(const std::string& color) {
        _color = color;
    }

    void add_input_edge(std::shared_ptr<Edge<T>> edge) {
        _input_edges.push_back(edge);
    }

    void add_output_edge(std::shared_ptr<Edge<T>> edge) {
        _output_edges.push_back(edge);
    }

    const std::vector<std::shared_ptr<Edge<T>>>& get_input_edges() const {
        return _input_edges;
    }

    const std::vector<std::shared_ptr<Edge<T>>>& get_output_edges() const {
        return _output_edges;
    }

    const std::string& get_name() const {
        return _name;
    }

    void set_name(const std::string& name) {
        _name = name;
    }

    bool has_neighbor(const std::string& neighbor_name) const {
        for (const auto& edge : _input_edges) {
            if (auto source = edge->get_source(); source && source->get_name() == neighbor_name) {
                return true;
            }
        }
        for (const auto& edge : _output_edges) {
            if (auto destination = edge->get_destination(); destination && destination->get_name() == neighbor_name) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::shared_ptr<Vertex<T>>> get_neighbors() const {
        std::vector<std::shared_ptr<Vertex<T>>> neighbors;

        for (const auto& edge : _input_edges) {
            if (auto source = edge->get_source(); source) {
                neighbors.push_back(source);
            }
        }

        for (const auto& edge : _output_edges) {
            if (auto destination = edge->get_destination(); destination) {
                neighbors.push_back(destination);
            }
        }

        return neighbors;
    }

    struct Hash {
        size_t operator()(const Vertex& vertex) const {
            return std::hash<std::string>{}(vertex.get_name());
        }
    };
};