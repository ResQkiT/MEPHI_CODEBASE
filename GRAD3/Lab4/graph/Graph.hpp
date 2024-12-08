#pragma once

#include <memory>
#include <utility>
#include <string>

#include "../../Lab3/HashMap.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"

#include <functional>
#include <memory>
#include <utility>


template<typename T>
struct std::hash<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>> {
    size_t operator()(const std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>& pair) const {
        auto hash1 = std::hash<std::string>()(pair.first->get_name());
        auto hash2 = std::hash<std::string>()(pair.second->get_name());
        return hash1 ^ (hash2 << 1);
    }
};

template<class T>
class Graph {
private:
    HashMap<std::string, std::shared_ptr<Vertex<T>>, typename Vertex<T>::Hash> _vertices;                   // vertices of the graph

    HashMap<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>, std::shared_ptr<Edge<T>>, 
            typename std::hash<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>> > _edges; // edges of the graph
    
    DynamicArray<std::string> _vertices_names;                                                              // vertices of the graph

public:
    Graph() : _vertices(), _edges(), _vertices_names(){}

    Graph(Graph& other) : _vertices(other._vertices), _edges(other._edges) , _vertices_names(other._vertices_names){}

    Graph(Graph&& other) noexcept :   
            _vertices(std::move(other._vertices)), 
            _edges(std::move(other._edges)),  
            _vertices_names(std::move(other._vertices_names)){}

    Graph& operator=(Graph& other) {
        if (this != &other) {
            _vertices = other._vertices;
            _edges = other._edges;
            _vertices_names = other._vertices_names;
        }
        return *this;
    }

    Graph& operator=(Graph&& other) noexcept {
        if (this != &other) {
            _vertices = std::move(other._vertices);
            _edges = std::move(other._edges);
            _vertices_names = std::move(other._vertices_names);
        }
        return *this;
    }

    void add_vertex(std::shared_ptr<Vertex<T>> vertex) {
        if (_vertices.find(vertex->get_name()).has_value())
        {
            return;
        }
        
        _vertices[vertex->get_name()] = vertex;
        _vertices_names.push_back(vertex->get_name());
    }

    void add_edge(std::shared_ptr<Vertex<T>> from, std::shared_ptr<Vertex<T>> to, std::shared_ptr<Edge<T>> edge) {
        edge->setSource(from);
        edge->setDestination(to);

        std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>> vertex_pair = std::make_pair(from, to);
        if(_edges.find(vertex_pair).has_value()){
            return;
        }
        _edges[vertex_pair] = edge;
    }

    void add_edge_by_names(const std::string& from_name, const std::string& to_name, std::shared_ptr<Edge<T>> edge) {
        auto from = get_vertex_by_name(from_name);
        auto to = get_vertex_by_name(to_name);
        if (!from || !to) {
            return;
        }
        add_edge(from, to, edge);
    }

    std::shared_ptr<Vertex<T>> get_vertex_by_name(const std::string& name) {
        if (!_vertices.find(name).has_value()) {
            return nullptr;
        }
        return _vertices[name];
    }

    std::shared_ptr<Edge<T>> get_edge_by_vertices(const std::shared_ptr<Vertex<T>>& from, const std::shared_ptr<Vertex<T>>& to) {
        std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>> vertex_pair = std::make_pair(from, to);
        if (!_edges.find(vertex_pair).has_value()) {
            return nullptr;
        }
        return _edges[vertex_pair];
    }

    std::string get_rod_string(bool is_directed) {
        std::string infix = is_directed ? " -> " : " -- ";
        std::string result = is_directed? "\ndigraph G {\n" : "\ngraph G {\n"; // Start with a directed graph

        for (const auto& vertex_name : _vertices_names) {
            auto vertex = get_vertex_by_name(vertex_name);
            result += vertex->get_name() + ";\n";
        }

        for (const auto& from_name : _vertices_names) {
            auto from_vertex = get_vertex_by_name(from_name);
            for (const auto& to_name : _vertices_names) {
                auto to_vertex = get_vertex_by_name(to_name);
                auto edge = get_edge_by_vertices(from_vertex, to_vertex);
                if (edge) {
                    result += from_vertex->get_name() + infix + to_vertex->get_name() + ";\n"; // Directed edge
                }
            }
        }

        result += "}\n"; // Close the graph
        return result;
    }


    void remove_vertex(const std::string& name) {
        if (!_vertices.find(name).has_value()) {
            return;
        }
        _vertices.erase(name);
        std::cout << "All ok!";
        _vertices_names.erase(std::find(_vertices_names.begin(), _vertices_names.end(), name) - _vertices_names.begin());
        // remove all edges connected to this vertex
        for (auto it = _edges.begin(); it != _edges.end(); it++) {
            if (it->first.first->get_name() == name || it->first.second->get_name() == name) {
                _edges.erase(it->first);
            }
        }

    }
};
