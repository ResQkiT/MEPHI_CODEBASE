#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <memory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Лабораторная работа №4");
    mainWindow.resize(1920, 1080);  

    auto centralWidget = std::make_unique<QWidget>(&mainWindow);
    auto mainLayout = std::make_unique<QHBoxLayout>(centralWidget.get());

    auto imageLabel = std::make_unique<QLabel>();
    imageLabel->setFixedSize(1080, 1080);
    imageLabel->setStyleSheet("border: 1px solid black;");
    imageLabel->setAlignment(Qt::AlignRight);

    auto menuLayout = std::make_unique<QVBoxLayout>();  
    menuLayout->setContentsMargins(10, 10, 10, 10);  // Устанавливаем отступы

    auto button = std::make_unique<QPushButton>("Нажми меня!", centralWidget.get());
    auto button2 = std::make_unique<QPushButton>("Нажми меня 2!", centralWidget.get());

    QObject::connect(button.get(), &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Сообщение", "Кнопка нажата!");
    });

    QObject::connect(button2.get(), &QPushButton::clicked, []() {
        QMessageBox::information(nullptr, "Сообщение", "Кнопка 2 нажата!");
    });

    menuLayout->addWidget(button.get()); 
    menuLayout->addWidget(button2.get());
    menuLayout->addStretch();  // Добавляем растяжение в конце компоновщик

    mainLayout->addLayout(menuLayout.get());  
    mainLayout->addWidget(imageLabel.get());  

    mainWindow.setCentralWidget(centralWidget.release());
    mainWindow.show();

    return app.exec();
}
