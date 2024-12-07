#pragma once

#include <memory>
#include <utility>
#include <string>

#include "../../Lab3/HashMap.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

#include <functional>
#include <memory>
#include <utility>


template<typename T>
struct std::hash<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>> {
    size_t operator()(const std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>& pair) const {
        auto hash1 = std::hash<std::shared_ptr<Vertex<T>>>()(pair.first);
        auto hash2 = std::hash<std::shared_ptr<Vertex<T>>>()(pair.second);
        return hash1 ^ (hash2 << 1);
    }
};

template<class T>
class Graph {
private:
    HashMap<std::string, std::shared_ptr<Vertex<T>>, typename Vertex<T>::Hash> _vertices;                   // vertices of the graph

    HashMap<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>, std::shared_ptr<Edge<T>>, 
            typename std::hash<std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>>> > _edges; // edges of the graph

public:
    Graph() : _vertices(), _edges() {}

    Graph(Graph& other) : _vertices(other._vertices), _edges(other._edges) {}

    Graph(Graph&& other) noexcept : _vertices(std::move(other._vertices)), _edges(std::move(other._edges)) {}

    Graph& operator=(Graph& other) {
        if (this != &other) {
            _vertices = other._vertices;
            _edges = other._edges;
        }
        return *this;
    }

    Graph& operator=(Graph&& other) noexcept {
        if (this != &other) {
            _vertices = std::move(other._vertices);
            _edges = std::move(other._edges);
        }
        return *this;
    }

    void add_vertex(std::shared_ptr<Vertex<T>> vertex) {
        _vertices[vertex->get_name()] = vertex;
    }

    void add_edge(std::shared_ptr<Vertex<T>> from, std::shared_ptr<Vertex<T>> to, std::shared_ptr<Edge<T>> edge) {
        std::pair<std::shared_ptr<Vertex<T>>, std::shared_ptr<Vertex<T>>> vertex_pair = std::make_pair(from, to);
        _edges[vertex_pair] = edge;
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
};
