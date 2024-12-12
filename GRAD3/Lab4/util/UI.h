#pragma once 

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <cstdlib>
#include <QPixmap>
#include <QLineEdit>
#include <QCheckBox>

#include "GraphRenderer.h"
#include "ImageRenderer.h"
#include "../graph/Graph.hpp"
#include "../graph/Edge.hpp"
#include "../graph/Vertex.hpp"
#include "../graph/DirectedEdge.hpp"
#include "../algorithms/GraphColoring.hpp"
#include "../algorithms/GraphColoring.hpp"

class UI : public QMainWindow {
    Q_OBJECT
public:
    UI(int argc, char *argv[], QApplication& app);
    ~UI();
    void run();

private:
    void addVertex();
    void addEdge();
    void removeVertex();
    void generateGraph();
    void coloringGraph();

private:
    QApplication& app_;
    std::unique_ptr<Graph<int>> graph_;
    bool is_graph_directed_;
    bool is_graph_bidirectional_;
    std::unique_ptr<GraphRenderer> graphRenderer_;

    // UI Components
    std::unique_ptr<QWidget> centralWidget_;
    std::unique_ptr<QHBoxLayout> mainLayout_;
    std::unique_ptr<QLabel> imageLabel_;
    std::unique_ptr<QVBoxLayout> menuLayout_;
    std::unique_ptr<QCheckBox> check_box_graph_directed_;
    std::unique_ptr<QCheckBox> check_box_graph_bidirectional_;
    std::unique_ptr<QHBoxLayout> layout_generate_graph_menu_;
    std::unique_ptr<QLabel> count_of_vertex_label_;
    std::unique_ptr<QLineEdit> enter_count_of_vertex_;
    std::unique_ptr<QLabel> probability_of_edge_;
    std::unique_ptr<QLineEdit> enter_probability_of_edge_;
    std::unique_ptr<QPushButton> button_generate_graph_;
    std::unique_ptr<QHBoxLayout> layout_add_vertex_line_;
    std::unique_ptr<QPushButton> button_add_vertex_;
    std::unique_ptr<QLineEdit> enter_line_vertex_name_;
    std::unique_ptr<QHBoxLayout> layout_add_edge_line_;
    std::unique_ptr<QPushButton> button_add_edge_;
    std::unique_ptr<QLineEdit> enter_line_edge_name_from_;
    std::unique_ptr<QLineEdit> enter_line_edge_name_to_;
    std::unique_ptr<QHBoxLayout> layout_remove_vertex_line_;
    std::unique_ptr<QPushButton> remove_vertex_;
    std::unique_ptr<QLineEdit> enter_line_remove_vertex_name_;
    std::unique_ptr<QPushButton> button_coloring_graph_;
};
