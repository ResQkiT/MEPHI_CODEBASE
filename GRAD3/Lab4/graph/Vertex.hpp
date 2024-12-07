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
    std::string _name;                                      // name of the vertex
    T _data;                                                // data stored in the vertex
    std::vector<std::shared_ptr<Edge<T>>> _input_edges;     // edges that point to this vertex
    std::vector<std::shared_ptr<Edge<T>>> _output_edges;    // edges that start from this vertex

public:

    Vertex(T data) 
        : _name(""), _data(std::move(data)) {}
    
    Vertex(const std::string& name) 
        : _name(name), _data(T()) {}
    
    Vertex(const std::string& name, T data) 
        : _name(name), _data(std::move(data)) {}
    
    Vertex(const Vertex<T>& vertex) = delete;               // copy of vertex is not allowed

    Vertex(Vertex<T>&& vertex) noexcept 
        : _name(std::move(vertex._name)),
          _data(std::move(vertex._data)), 
          _input_edges(std::move(vertex._input_edges)),  
          _output_edges(std::move(vertex._output_edges)) {}

    Vertex<T>& operator=(const Vertex<T>& vertex) = delete; // copy assignment is not allowed

    Vertex<T>& operator=(Vertex<T>&& vertex) noexcept {
        if (this != &vertex) {
            _name = std::move(vertex._name);
            _data = std::move(vertex._data);
            _input_edges = std::move(vertex._input_edges);
            _output_edges = std::move(vertex._output_edges);
        }
        return *this;
    }

    T get_data() const {
        return _data;
    }

    void set_data(const T& data) {
        _data = data;
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

    struct Hash {
        size_t operator()(const Vertex& vertex) const {
            return std::hash<std::string>{}(vertex.get_name());
        }
    };
};
