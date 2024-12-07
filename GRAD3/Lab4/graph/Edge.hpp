#pragma once

#include <memory>
#include <utility>
#include <string>   

#include "IHaveWeight.h"
#include "Vertex.hpp"

template<class T>
class Edge{
private:
    std::shared_ptr<Vertex<T>> _source;
    std::shared_ptr<Vertex<T>> _destination;

public:
    Edge() = default;
    Edge(std::shared_ptr<Vertex<T>> source, std::shared_ptr<Vertex<T>> destination){
        this->_source = source;
        this->_destination = destination;
    }

    virtual ~Edge() = default; 

    std::pair<std::shared_ptr<Vertex<T>> , std::shared_ptr<Vertex<T>> > endpoints() const {
        return std::make_pair(_source, _destination);
    }

    void setSource(std::shared_ptr<Vertex<T>> source){
        this->_source = source;
    }

    void setDestination(std::shared_ptr<Vertex<T>>  destination){
        this->_destination = destination;
    }

    virtual std::string to_string() const {
        return _source->get_name() + " -- " + _destination->get_name();
    }

    struct Hash {
        size_t operator()(const Edge& edge) const {
            return std::hash<std::string>{}(edge.to_string());
        }
    };
};