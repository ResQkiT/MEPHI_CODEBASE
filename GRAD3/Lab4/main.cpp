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

#include "util/GraphRenderer.h"
#include "util/ImageRenderer.h"
#include "test.h"
#include "graph/Graph.hpp"
#include "graph/Edge.hpp"
#include "graph/Vertex.hpp"


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

    //--------------------Utility
    auto graphRenderer = std::make_unique<GraphRenderer>("temp/");
    

    auto graph = std::make_unique<Graph<int>>();
    //--------------------Interface Components
    auto centralWidget = std::make_unique<QWidget>(&mainWindow);
    auto mainLayout = std::make_unique<QHBoxLayout>(centralWidget.get());
    auto imageLabel = std::make_unique<QLabel>();

    auto menuLayout = std::make_unique<QVBoxLayout>();
    
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

    //--------------------Interface initialization
    imageLabel->setFixedSize(1080, 1080);
    imageLabel->setStyleSheet("border: 1px solid black;");
    imageLabel->setAlignment(Qt::AlignCenter);
    menuLayout->setContentsMargins(10, 10, 10, 10); 

    //--------------------Buttons functors    
    QObject::connect(button_add_vertex.get(), &QPushButton::clicked, [&]() {
        QString name = enter_line_vertex_name->text(); 
        auto vertex = std::make_shared<Vertex<int>>(name.toStdString());
        
        graph->add_vertex(vertex);
        
        graphRenderer->render(graph->get_rod_string(), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });

    QObject::connect(button_add_egde.get(), &QPushButton::clicked, [&]() {
        QString from_name = enter_line_edge_name_from->text();
        QString to_name = enter_line_edge_name_to->text();

        auto edge = std::make_shared<Edge<int>>();

        graph->add_edge_by_names(from_name.toStdString(), to_name.toStdString(), edge);
        std::cout << graph->get_rod_string() << "\n";

        graphRenderer->render(graph->get_rod_string(), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });

    QObject::connect(remove_vertex.get(), &QPushButton::clicked, [&]() {
        QString name = enter_line_remove_vertex_name->text();
        graph->remove_vertex(name.toStdString());
        graphRenderer->render(graph->get_rod_string(), "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });
    //--------------------Linking Components
    layout_add_edge_line->addWidget(button_add_vertex.get()); 
    layout_add_edge_line->addWidget(enter_line_vertex_name.get());
    
    layout_add_vertex_line->addWidget(button_add_egde.get());
    layout_add_vertex_line->addWidget(enter_line_edge_name_from.get());
    layout_add_vertex_line->addWidget(enter_line_edge_name_to.get());

    layout_remove_vertex_line->addWidget(remove_vertex.get());
    layout_remove_vertex_line->addWidget(enter_line_remove_vertex_name.get());

    menuLayout->addLayout(layout_add_edge_line.get());
    menuLayout->addLayout(layout_add_vertex_line.get());
    menuLayout->addLayout(layout_remove_vertex_line.get());

    menuLayout->addStretch();  

    mainLayout->addLayout(menuLayout.get());  
    mainLayout->addWidget(imageLabel.get());  

    mainWindow.setCentralWidget(centralWidget.release());
    mainWindow.show();

    return app.exec();
}
