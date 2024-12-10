#pragma once

#include <string>
#include "../graph/Graph.hpp"
#include "../graph/Edge.hpp"
#include "../graph/Vertex.hpp"

template <class T>
class Graph;

template <class T>
class IExecutable {
public:
    virtual ~IExecutable() = default;

    virtual void execute(Graph<T>& graph) = 0;

};