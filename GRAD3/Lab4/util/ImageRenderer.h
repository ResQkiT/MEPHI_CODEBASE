#pragma once
#include <QLabel>
#include <string>

class ImageRenderer{
public:
    ImageRenderer() = delete;

    static void render(QLabel& image_holder, const std::string& filename);
};