#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <cassert>
#include <memory>
#include <vector>
#include <random>
#include <iomanip> 

#include "graph/Graph.hpp"
#include "graph/Vertex.hpp" 
#include "graph/Edge.hpp"

namespace test{
    void testVertexConstructor() {
        Vertex<int> vertex(10);
        assert(vertex.get_data() == 10);
    }

    void testVertexMoveConstructor() {
        Vertex<int> vertex1(20);
        Vertex<int> vertex2(std::move(vertex1));
        assert(vertex2.get_data() == 20);
    }

    void testVertexSetData() {
        Vertex<int> vertex(30);
        vertex.set_data(40);
        assert(vertex.get_data() == 40);
    }

    void testVertexAddInputEdge() {
        Vertex<int> vertex(50);
        auto edge = std::make_shared<Edge<int>>(nullptr, nullptr); 
        vertex.add_input_edge(edge);
        assert(vertex.get_input_edges().size() == 1);
    }

    void testVertexAddOutputEdge() {
        Vertex<int> vertex(60);
        auto edge = std::make_shared<Edge<int>>(nullptr, nullptr);
        vertex.add_output_edge(edge);
        assert(vertex.get_output_edges().size() == 1);
    }



    void testEdgeConstructor() {
        auto source = std::make_shared<Vertex<int>>(60);
        auto destination = std::make_shared<Vertex<int>>(70);
        Edge<int> edge(source, destination);
        auto endpoints = edge.endpoints();
        assert(endpoints.first == source);
        assert(endpoints.second == destination);
    }

    void testEdgeSetSourceAndDestination() {
        auto source = std::make_shared<Vertex<int>>(80);
        auto destination = std::make_shared<Vertex<int>>(90);
        Edge<int> edge;
        edge.setSource(source);
        edge.setDestination(destination);
        auto endpoints = edge.endpoints();
        assert(endpoints.first == source);
        assert(endpoints.second == destination);
    }

    void testEdgeToString() {
        auto source = std::make_shared<Vertex<int>>("first", 100);
        source->set_data(1);
        auto destination = std::make_shared<Vertex<int>>("second", 110);
        destination->set_data(2); 
        Edge<int> edge(source, destination);
        std::string expected = "first -- second";
        assert(edge.to_string() == expected);
    }

    void testGraphAddVertex() {
        Graph<int> graph;
        auto vertex = std::make_shared<Vertex<int>>("Vertex1");
        graph.add_vertex(vertex);
        assert(graph.get_vertex_by_name("Vertex1") == vertex);
    }

    void testGraphAddEdge() {
        Graph<int> graph;
        auto vertex1 = std::make_shared<Vertex<int>>("Vertex1");
        auto vertex2 = std::make_shared<Vertex<int>>("Vertex2");
        auto edge = std::make_shared<Edge<int>>(vertex1, vertex2); // Предполагается, что конструктор Edge принимает вершины

        graph.add_vertex(vertex1);
        graph.add_vertex(vertex2);
        graph.add_edge(vertex1, vertex2, edge);

        assert(graph.get_edge_by_vertices(vertex1, vertex2) == edge);
    }

    void testGraphGetNonExistentVertex() {
        Graph<int> graph;
        assert(graph.get_vertex_by_name("NonExistent") == nullptr);
    }

    void testGraphGetNonExistentEdge() {
        Graph<int> graph;
        auto vertex1 = std::make_shared<Vertex<int>>("Vertex1");
        auto vertex2 = std::make_shared<Vertex<int>>("Vertex2");

        graph.add_vertex(vertex1);
        graph.add_vertex(vertex2);
        assert(graph.get_edge_by_vertices(vertex1, vertex2) == nullptr);
    }

    void testGraphCopyConstructor() {
        Graph<int> graph;
        auto vertex = std::make_shared<Vertex<int>>("Vertex1");
        auto edge = std::make_shared<Edge<int>>(vertex, vertex);

        graph.add_vertex(vertex);
        graph.add_edge(vertex, vertex, edge);

        Graph<int> copiedGraph(graph);
        assert(copiedGraph.get_vertex_by_name("Vertex1") == vertex);
        assert(copiedGraph.get_edge_by_vertices(vertex, vertex) == edge);
    }

    void testGraphMoveConstructor() {
        Graph<int> graph;
        auto vertex = std::make_shared<Vertex<int>>("Vertex1");
        auto edge = std::make_shared<Edge<int>>(vertex, vertex);

        graph.add_vertex(vertex);
        graph.add_edge(vertex, vertex, edge);

        Graph<int> movedGraph(std::move(graph));
        assert(movedGraph.get_vertex_by_name("Vertex1") == vertex);
        assert(movedGraph.get_edge_by_vertices(vertex, vertex) == edge);
    }

    void testGraphCopyAssignmentOperator() {
        Graph<int> graph;
        auto vertex = std::make_shared<Vertex<int>>("Vertex1");
        auto edge = std::make_shared<Edge<int>>(vertex, vertex);

        graph.add_vertex(vertex);
        graph.add_edge(vertex, vertex, edge);

        Graph<int> anotherGraph;
        anotherGraph = graph;
        assert(anotherGraph.get_vertex_by_name("Vertex1") == vertex);
        assert(anotherGraph.get_edge_by_vertices(vertex, vertex) == edge);
    }

    void testGraphMoveAssignmentOperator() {
        Graph<int> graph;
        auto vertex = std::make_shared<Vertex<int>>("Vertex1");
        auto edge = std::make_shared<Edge<int>>(vertex, vertex);

        graph.add_vertex(vertex);
        graph.add_edge(vertex, vertex, edge);

        Graph<int> anotherGraph;
        anotherGraph = std::move(graph);
        assert(anotherGraph.get_vertex_by_name("Vertex1") == vertex);
        assert(anotherGraph.get_edge_by_vertices(vertex, vertex) == edge);
    }

    int all_test() {
        std::map<std::string, std::function<void()>> testMap = {    
            {"testVertexConstructor", testVertexConstructor},
            {"testVertexMoveConstructor", testVertexMoveConstructor},
            {"testSetData", testVertexSetData},
            {"testAddInputEdge", testVertexAddInputEdge},
            {"testAddOutputEdge", testVertexAddOutputEdge},

            {"testEdgeConstructor", testEdgeConstructor},
            {"testEdgeSetSourceAndDestination", testEdgeSetSourceAndDestination},
            {"testEdgeToString", testEdgeToString},

            {"testGraphAddVertex", testGraphAddVertex},
            {"testGraphAddEdge", testGraphAddEdge},
            {"testGraphGetNonExistentVertex", testGraphGetNonExistentVertex},
            {"testGraphGetNonExistentEdge", testGraphGetNonExistentEdge},
            {"testGraphCopyConstructor", testGraphCopyConstructor},
            {"testGraphMoveConstructor", testGraphMoveConstructor},
            {"testGraphCopyAssignmentOperator", testGraphCopyAssignmentOperator},
            {"testGraphMoveAssignmentOperator", testGraphMoveAssignmentOperator}
            

        };

        for (const auto& [testName, testFunc] : testMap) {
            std::cout << "Running test: " << testName << "...";
            testFunc();
            std::cout << "PASSED!\n";
        }

        std::cout << "All tests passed!\n";
        return 0;
    }
};

void run_test(){
    test::all_test();
}