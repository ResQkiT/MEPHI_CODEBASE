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

#include "util/GraphRenderer.h"
#include "util/ImageRenderer.h"
#include "test.h"

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        run_test();
        return 0;
    }

    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Лабораторная работа №4");
    mainWindow.resize(1920, 1080);  

    auto graphRenderer = std::make_unique<GraphRenderer>("temp/");

    auto centralWidget = std::make_unique<QWidget>(&mainWindow);
    auto mainLayout = std::make_unique<QHBoxLayout>(centralWidget.get());
    auto imageLabel = std::make_unique<QLabel>();
    imageLabel->setFixedSize(1080, 1080);
    imageLabel->setStyleSheet("border: 1px solid black;");
    imageLabel->setAlignment(Qt::AlignCenter);

    auto menuLayout = std::make_unique<QVBoxLayout>();  
    menuLayout->setContentsMargins(10, 10, 10, 10); 

    auto button = std::make_unique<QPushButton>("Нажми меня!", centralWidget.get());
    auto button2 = std::make_unique<QPushButton>("Нажми меня 2!", centralWidget.get());

    QObject::connect(button.get(), &QPushButton::clicked, [&]() {
        graphRenderer->render("digraph G {A -> B; B -> C; A -> C; }", "file1.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file1.png");
    });

    QObject::connect(button2.get(), &QPushButton::clicked, [&]() {
        graphRenderer->render("digraph { a -> b }", "file2.png");
        ImageRenderer::render(*imageLabel.get(), "temp/file2.png");
    });

    menuLayout->addWidget(button.get()); 
    menuLayout->addWidget(button2.get());
    menuLayout->addStretch();  

    mainLayout->addLayout(menuLayout.get());  
    mainLayout->addWidget(imageLabel.get());  

    mainWindow.setCentralWidget(centralWidget.release());
    mainWindow.show();

    return app.exec();
}
