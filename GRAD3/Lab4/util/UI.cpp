#include "UI.h"

UI::UI(int argc, char *argv[], QApplication& app)
    : QMainWindow(), app_(app), is_graph_directed_(false), is_graph_bidirectional_(false) {
    graphRenderer_ = std::make_unique<GraphRenderer>("temp/");
    graph_ = std::make_unique<Graph<int>>();

    // Set up the main window
    setWindowTitle("Лабораторная работа №4");
    resize(1920, 1080);
    setStyleSheet("background-color: white;");

    // Central Widget and Layout
    centralWidget_ = std::make_unique<QWidget>(this);
    mainLayout_ = std::make_unique<QHBoxLayout>(centralWidget_.get());
    setCentralWidget(centralWidget_.get());

    // Image Label
    imageLabel_ = std::make_unique<QLabel>();
    imageLabel_->setStyleSheet("border: 1px solid black;");
    imageLabel_->setMaximumSize(1600, 1080);
    imageLabel_->setMinimumSize(1080, 1080);
    imageLabel_->setAlignment(Qt::AlignCenter);

    // Menu Layout
    menuLayout_ = std::make_unique<QVBoxLayout>();
    menuLayout_->setContentsMargins(10, 10, 10, 10);

    // Check Boxes
    check_box_graph_directed_ = std::make_unique<QCheckBox>("Граф направленный->", centralWidget_.get());
    check_box_graph_bidirectional_ = std::make_unique<QCheckBox>("Граф двунаправленный->", centralWidget_.get());

    // Generate Graph Menu
    layout_generate_graph_menu_ = std::make_unique<QHBoxLayout>();
    count_of_vertex_label_ = std::make_unique<QLabel>("Количество вершин:");
    enter_count_of_vertex_ = std::make_unique<QLineEdit>();
    enter_count_of_vertex_->setFixedWidth(50);
    probability_of_edge_ = std::make_unique<QLabel>("Вероятность ребра:");
    enter_probability_of_edge_ = std::make_unique<QLineEdit>();
    enter_probability_of_edge_->setFixedWidth(50);
    button_generate_graph_ = std::make_unique<QPushButton>("Сгенерировать граф", centralWidget_.get());

    layout_generate_graph_menu_->addWidget(count_of_vertex_label_.get());
    layout_generate_graph_menu_->addWidget(enter_count_of_vertex_.get());
    layout_generate_graph_menu_->addWidget(probability_of_edge_.get());
    layout_generate_graph_menu_->addWidget(enter_probability_of_edge_.get());
    layout_generate_graph_menu_->addWidget(button_generate_graph_.get());
    layout_generate_graph_menu_->addStretch();

    // Add Vertex Line
    layout_add_vertex_line_ = std::make_unique<QHBoxLayout>();
    button_add_vertex_ = std::make_unique<QPushButton>("Добавить вершину", centralWidget_.get());
    enter_line_vertex_name_ = std::make_unique<QLineEdit>();

    layout_add_vertex_line_->addWidget(button_add_vertex_.get());
    layout_add_vertex_line_->addWidget(enter_line_vertex_name_.get());

    // Add Edge Line
    layout_add_edge_line_ = std::make_unique<QHBoxLayout>();
    button_add_edge_ = std::make_unique<QPushButton>("Добавить ребро", centralWidget_.get());
    enter_line_edge_name_from_ = std::make_unique<QLineEdit>();
    enter_line_edge_name_to_ = std::make_unique<QLineEdit>();

    layout_add_edge_line_->addWidget(button_add_edge_.get());
    layout_add_edge_line_->addWidget(enter_line_edge_name_from_.get());
    layout_add_edge_line_->addWidget(enter_line_edge_name_to_.get());

    // Remove Vertex Line
    layout_remove_vertex_line_ = std::make_unique<QHBoxLayout>();
    remove_vertex_ = std::make_unique<QPushButton>("Удалить вершину", centralWidget_.get());
    enter_line_remove_vertex_name_ = std::make_unique<QLineEdit>();

    layout_remove_vertex_line_->addWidget(remove_vertex_.get());
    layout_remove_vertex_line_->addWidget(enter_line_remove_vertex_name_.get());

    // Coloring Graph Button
    button_coloring_graph_ = std::make_unique<QPushButton>("Раскрасить граф", centralWidget_.get());

    // Add to Menu Layout
    menuLayout_->addLayout(layout_generate_graph_menu_.get());
    menuLayout_->addWidget(check_box_graph_directed_.get());
    menuLayout_->addWidget(check_box_graph_bidirectional_.get());
    menuLayout_->addLayout(layout_add_vertex_line_.get());
    menuLayout_->addLayout(layout_add_edge_line_.get());
    menuLayout_->addLayout(layout_remove_vertex_line_.get());
    menuLayout_->addWidget(button_coloring_graph_.get());
    menuLayout_->addStretch();

    // Main Layout
    mainLayout_->addLayout(menuLayout_.get());
    mainLayout_->addWidget(imageLabel_.get());

    // Signal-Slot Connections
    connect(button_add_vertex_.get(), &QPushButton::clicked, this, &UI::addVertex);
    connect(button_add_edge_.get(), &QPushButton::clicked, this, &UI::addEdge);
    connect(remove_vertex_.get(), &QPushButton::clicked, this, &UI::removeVertex);
    connect(button_generate_graph_.get(), &QPushButton::clicked, this, &UI::generateGraph);
    connect(button_coloring_graph_.get(), &QPushButton::clicked, this, &UI::coloringGraph);
    connect(check_box_graph_directed_.get(), &QCheckBox::stateChanged, [this](int state) {
        is_graph_directed_ = state == Qt::Checked;
    });
    connect(check_box_graph_bidirectional_.get(), &QCheckBox::stateChanged, [this](int state) {
        is_graph_bidirectional_ = state == Qt::Checked;
    });
}

void UI::run() {
    show();
    app_.exec();
}

void UI::addVertex() {
    QString name = enter_line_vertex_name_->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите имя вершины.");
        return;
    }
    graph_->add_vertex(std::make_shared<Vertex<int>>(name.toStdString()));
    graphRenderer_->render(graph_->get_rod_string(is_graph_directed_), "file1.png");
    ImageRenderer::render(*imageLabel_.get(), "temp/file1.png");
    enter_line_vertex_name_->clear();
}

void UI::addEdge() {
    QString from_name = enter_line_edge_name_from_->text();
    QString to_name = enter_line_edge_name_to_->text();
    if (from_name.isEmpty() || to_name.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите имена вершин.");
        return;
    }
    std::shared_ptr<Edge<int>> edge;
    if (is_graph_directed_) {
        edge = std::make_shared<DirectedEdge<int>>();
    } else {
        edge = std::make_shared<Edge<int>>();
    }
    graph_->add_edge_by_names(from_name.toStdString(), to_name.toStdString(), edge);
    graphRenderer_->render(graph_->get_rod_string(is_graph_directed_), "file1.png");
    ImageRenderer::render(*imageLabel_.get(), "temp/file1.png");
    enter_line_edge_name_from_->clear();
    enter_line_edge_name_to_->clear();
}

void UI::removeVertex() {
    QString name = enter_line_remove_vertex_name_->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Введите имя вершины.");
        return;
    }
    graph_->remove_vertex(name.toStdString());
    graphRenderer_->render(graph_->get_rod_string(is_graph_directed_), "file1.png");
    ImageRenderer::render(*imageLabel_.get(), "temp/file1.png");
    enter_line_remove_vertex_name_->clear();
}

void UI::generateGraph() {
    bool ok;
    int vertex_count = enter_count_of_vertex_->text().toInt(&ok);
    if (!ok || vertex_count <= 0) {
        QMessageBox::warning(this, "Внимание", "Введите корректное количество вершин.");
        return;
    }
    double edge_probability = enter_probability_of_edge_->text().toDouble(&ok);
    if (!ok || edge_probability < 0.0 || edge_probability > 1.0) {
        QMessageBox::warning(this, "Внимание", "Введите корректную вероятность ребра.");
        return;
    }
    graph_ = std::make_unique<Graph<int>>(Graph<int>::generate_graph(vertex_count, edge_probability, is_graph_directed_, is_graph_bidirectional_));
    graphRenderer_->render(graph_->get_rod_string(is_graph_directed_), "file1.png");
    ImageRenderer::render(*imageLabel_.get(), "temp/file1.png");
    // enter_count_of_vertex_->clear();
    // enter_probability_of_edge_->clear();
}

void UI::coloringGraph() {
    GraphColoring<int> coloring;
    coloring.execute(*graph_.get());
    graphRenderer_->render(graph_->get_rod_string(is_graph_directed_), "file1.png");
    ImageRenderer::render(*imageLabel_.get(), "temp/file1.png");
}

UI::~UI() = default;