#pragma once

#include "Edge.hpp"

template<class T>
class DirectedEdge : public Edge<T> {
public:
    DirectedEdge() : Edge<T>() {}

    DirectedEdge(std::shared_ptr<Vertex<T>> source, std::shared_ptr<Vertex<T>> destination)
        : Edge<T>(source, destination){}

    virtual ~DirectedEdge() = default;

    virtual std::string to_string() const override {
        return this->_source->get_name() + " -> " + this->_destination->get_name();
    }

    virtual bool is_directed() const override{
        return true;
    }
};
