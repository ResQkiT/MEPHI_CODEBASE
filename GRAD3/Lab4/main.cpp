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

#include "util/GraphRenderer.h"
#include "util/ImageRenderer.h"
#include "test.h"
#include "graph/Graph.hpp"
#include "graph/Edge.hpp"
#include "graph/Vertex.hpp"
#include "graph/DirectedEdge.hpp"
#include "algorithms/GraphColoring.hpp"

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        run_test();
        return 0;
    }

    //--------------------Main components
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Лабораторная работа №4");
    mainWindow.resize(1920, 1080);  
    mainWindow.setStyleSheet("background-color: white;");
    //--------------------Utility
    auto graphRenderer = std::make_unique<GraphRenderer>("temp/");
    

    auto graph = std::make_unique<Graph<int>>();
    bool is_graph_directed = false;
    bool is_graph_bidirectional = false;
    //--------------------Interface Components
    auto centralWidget = std::make_unique<QWidget>(&mainWindow);
    auto mainLayout = std::make_unique<QHBoxLayout>(centralWidget.get());
    auto imageLabel = std::make_unique<QLabel>();

    auto menuLayout = std::make_unique<QVBoxLayout>();
    
    auto check_box_graph_directed = std::make_unique<QCheckBox>("Граф направленный->", centralWidget.get());
    auto check_box_graph_bidirectional = std::make_unique<QCheckBox>("Граф двунаправленный->", centralWidget.get());

    auto layout_generate_graph_menu = std::make_unique<QHBoxLayout>();
    auto count_of_vertex_label = std::make_unique<QLabel>("Количество вершин:");
    auto enter_count_of_vertex = std::make_unique<QLineEdit>();
    auto probability_of_edge = std::make_unique<QLabel>("Вероятность ребра:");
    auto enter_probability_of_edge = std::make_unique<QLineEdit>();
    auto button_generate_graph = std::make_unique<QPushButton>("Сгенерировать граф", centralWidget.get());

    auto layout_add_vertex_line = std::make_unique<QHBoxLayout>();
    auto button_add_vertex = std::make_unique<QPushButton>("Добавить вершину", centralWidget.get());
    auto enter_line_vertex_name = std::make_unique<QLineEdit>();

    auto layout_add_edge_line = std::make_unique<QHBoxLayout>();
    auto button_add_egde = std::make_unique<QPushButton>("Добавить ребро", centralWidget.get());
    auto enter_line_edge_name_from = std::make_unique<QLineEdit>();
    auto enter_line_edge_name_to = std::make_unique<QLineEdit>();

    auto layout_remove_vertex_line = std::make_unique<QHBoxLayout>();
    auto remove_vertex = std::make_unique<QPushButton>("Удалить вершину", centralWidget.get());
    auto enter_line_remove_vertex_name = std::make_unique<QLineEdit>();

    auto button_coloring_graph = std::make_unique<QPushButton>("Раскрасить гарф", centralWidget.get());

    //--------------------Interface initialization
    // imageLabel->setFixedSize(1080, 1080);
    imageLabel->setStyleSheet("border: 1px solid black;");
    imageLabel->setMaximumSize(1600, 1080);
    imageLabel->setMinimumSize(1080, 1080);
    imageLabel->setAlignment(Qt::AlignCenter);
    menuLayout->setContentsMargins(10, 10, 10, 10); 
    enter_count_of_vertex->setAlignment(Qt::AlignLeft);
    enter_count_of_vertex->setFixedWidth(50);
    enter_probability_of_edge->setFixedWidth(50);

    //--------------------Buttons functors    
    QObject::connect(button_add_vertex.get(), &QPushButton::clicked, [&]() {
        QString name = enter_line_vertex_name->text(); 
        auto vertex = std::make_shared<Vertex<int>>(name.toStdString());
        
        graph->add_vertex(vertex);
        
        graphRenderer->render(graph->get_rod_string(is_graph_directed), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });

    QObject::connect(button_add_egde.get(), &QPushButton::clicked, [&]() {
        QString from_name = enter_line_edge_name_from->text();
        QString to_name = enter_line_edge_name_to->text();

        
        std::shared_ptr<Edge<int>> edge;

        if (is_graph_directed) {
            edge = std::make_shared<DirectedEdge<int>>();
        } else {
            edge = std::make_shared<Edge<int>>();
        }

        graph->add_edge_by_names(from_name.toStdString(), to_name.toStdString(), edge);
        std::cout << graph->get_rod_string(is_graph_directed) << "\n";

        graphRenderer->render(graph->get_rod_string(is_graph_directed), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });

    QObject::connect(remove_vertex.get(), &QPushButton::clicked, [&]() {
        QString name = enter_line_remove_vertex_name->text();
        graph->remove_vertex(name.toStdString());
        graphRenderer->render(graph->get_rod_string(is_graph_directed), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });

    QObject::connect(check_box_graph_directed.get(), &QCheckBox::stateChanged, [&](int state) {
        is_graph_directed  = state == Qt::Checked;
    });

    QObject::connect(check_box_graph_bidirectional.get(), &QCheckBox::stateChanged, [&](int state) {
        is_graph_bidirectional = state == Qt::Checked;
    });
    
    QObject::connect(button_generate_graph.get(), &QPushButton::clicked, [&]() {
        //генерация графа
        std::string count = enter_count_of_vertex->text().toStdString();
        std::string probability = enter_probability_of_edge->text().toStdString();

        size_t vertex_count = std::stoi(count);
        double edge_probability = std::stod(probability);

        std::cout << vertex_count << " " << edge_probability<< " \n";
        graph = std::make_unique<Graph<int>>(Graph<int>::generate_graph(vertex_count, edge_probability, is_graph_directed, is_graph_bidirectional));
        std::cout << graph->get_rod_string(is_graph_directed) << "\n";

        graphRenderer->render(graph->get_rod_string(is_graph_directed), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");

    });

    QObject::connect(button_coloring_graph.get(), &QPushButton::clicked, [&]() {
        GraphColoring<int> coloring;
        coloring.execute(*graph.get());

        graphRenderer->render(graph->get_rod_string(is_graph_directed), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });
    //--------------------Linking Components
    layout_generate_graph_menu->addWidget(count_of_vertex_label.get());
    layout_generate_graph_menu->addWidget(enter_count_of_vertex.get());
    layout_generate_graph_menu->addWidget(probability_of_edge.get());
    layout_generate_graph_menu->addWidget(enter_probability_of_edge.get());
    layout_generate_graph_menu->addWidget(button_generate_graph.get());
    layout_generate_graph_menu->addStretch();

    layout_add_edge_line->addWidget(button_add_vertex.get()); 
    layout_add_edge_line->addWidget(enter_line_vertex_name.get());
    
    layout_add_vertex_line->addWidget(button_add_egde.get());
    layout_add_vertex_line->addWidget(enter_line_edge_name_from.get());
    layout_add_vertex_line->addWidget(enter_line_edge_name_to.get());

    layout_remove_vertex_line->addWidget(remove_vertex.get());
    layout_remove_vertex_line->addWidget(enter_line_remove_vertex_name.get());

    menuLayout->addLayout(layout_generate_graph_menu.get());
    menuLayout->addWidget(check_box_graph_directed.get());
    menuLayout->addWidget(check_box_graph_bidirectional.get());
    menuLayout->addLayout(layout_add_edge_line.get());
    menuLayout->addLayout(layout_add_vertex_line.get());
    menuLayout->addLayout(layout_remove_vertex_line.get());
    menuLayout->addWidget(button_coloring_graph.get());

    menuLayout->addStretch();  

    mainLayout->addLayout(menuLayout.get());  
    mainLayout->addWidget(imageLabel.get());  

    mainWindow.setCentralWidget(centralWidget.release());
    mainWindow.show();

    return app.exec();
}
