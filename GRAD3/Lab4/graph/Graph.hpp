#pragma once

#include <memory>
#include <utility>
#include <string>

#include "../../Lab3/HashMap.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"
#include "../algorithms/IExecutable.hpp"

#include <functional>
#include <memory>
#include <utility>
#include <random>


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
    static Graph<T> generate_graph( size_t count_of_vertex, 
                                    double edge_probability, 
                                    bool directed = false, 
                                    bool is_bidirectional = false) {
        Graph<T> graph;
        std::string prefix = "Vertex";
        is_bidirectional = is_bidirectional && directed; //ненаправленный граф не может быть двунаправленным
        
        
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (size_t i = 1; i <= count_of_vertex; ++i) {
            std::string name = prefix + std::to_string(i);
            std::shared_ptr<Vertex<T>> vertex = std::make_shared<Vertex<T>>(name);
            graph.add_vertex(vertex);
        }


        for (size_t i = 1; i <= count_of_vertex; ++i) {
            auto from_vertex = graph.get_vertex_by_name(prefix + std::to_string(i));
            for (size_t j = 1; j <= count_of_vertex; ++j) {
                if (i == j) continue; 
                auto to_vertex = graph.get_vertex_by_name(prefix + std::to_string(j));
                if (is_bidirectional || i < j) { 
                    if (dist(generator) < edge_probability) {
                        auto edge = std::make_shared<Edge<T>>(from_vertex, to_vertex);
                        graph.add_edge_by_names(prefix + std::to_string(i), prefix + std::to_string(j), edge);
                    }
                }
            }
        }
        return graph;
    }
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
        edge->set_source(from);
        edge->set_destination(to);
        
        from->add_output_edge(edge);
        to->add_input_edge(edge);

        auto vertex_pair = std::make_pair(from, to);
        if(_edges.find(vertex_pair).has_value()){
            std::cout << "Not  added here!!!!" <<"\n";
            return;
        }
        
        _edges[vertex_pair] = edge;
    }

    void add_edge_by_names(const std::string& from_name, const std::string& to_name, std::shared_ptr<Edge<T>> edge) {
        auto from = get_vertex_by_name(from_name);
        auto to = get_vertex_by_name(to_name);
        if (!from || !to || from->get_name() == to->get_name()) {
            std::cout << "Not  added!!!!" <<"\n";
            return;
        }
        add_edge(from, to, edge);
    }
    
    std::shared_ptr<Edge<T>> get_edge_by_vertices(const std::shared_ptr<Vertex<T>> from, const std::shared_ptr<Vertex<T>> to) {
        std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>> vertex_pair = std::make_pair(from, to);
        if (!_edges.find(vertex_pair).has_value()) {
            return nullptr;
        }
        return _edges[vertex_pair];
    }

    std::shared_ptr<Vertex<T>> get_vertex_by_name(const std::string& name) {
        if (!_vertices.find(name).has_value()) {
            return nullptr;
        }
        return _vertices[name];
    }

    std::string get_rod_string(bool is_directed) {
        std::string infix = is_directed ? " -> " : " -- ";
        std::string result = is_directed ? "digraph G {\n" : "graph G {\n";
        result += "layout=\"sfdp\" beautify=true;\n";
        DynamicArray<std::string> vertexNames = _vertices_names;
        
        for (size_t i = 0; i < vertexNames.get_size(); ++i) {
            std::string name = vertexNames[i];
            auto vertex = get_vertex_by_name(name);
            if (vertex != nullptr) {
                result += vertex->get_name() +"[color="+vertex->get_color()+"];\n";
            }
        }
        
        for (size_t bucketIndex = 0; bucketIndex < _edges.hash_table.get_size(); ++bucketIndex) {
            auto bucket = _edges.hash_table[bucketIndex];
            for (size_t itemIndex = 0; itemIndex < bucket.get_size(); ++itemIndex) {
                auto item = bucket.get(itemIndex);
                std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>> vertexPair = item.first;

                if (vertexPair.first != nullptr && vertexPair.second != nullptr) {
                    // if ((!is_directed && vertexPair.first->get_name() > vertexPair.second->get_name()) ){
                    //     continue;
                    // }
                    result += vertexPair.first->get_name() + infix + vertexPair.second->get_name() + ";\n";
                }
            }
        }
        
        result += "}\n";
        std::cout << "result " << result<<'\n';
        return result;
    }


    void remove_vertex(const std::string& name) {
        if (!_vertices.find(name).has_value()) return;
        
        std::vector<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>> edges_to_remove;
        for (const auto& edge_pair : _edges) {
            if (edge_pair.first.first->get_name() == name || edge_pair.first.second->get_name() == name)
                edges_to_remove.push_back(edge_pair.first);
        }
        
        for (const auto& pair : edges_to_remove) _edges.erase(pair);
        _vertices.erase(name);
        _vertices_names.erase(std::find(_vertices_names.begin(), _vertices_names.end(), name) - _vertices_names.begin());
    }

    template<class U>
    friend class GraphColoring;
};
