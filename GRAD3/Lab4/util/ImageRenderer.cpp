#include "ImageRenderer.h"
#include <QPixmap>
#include <QString>

void ImageRenderer::render(QLabel& image_holder, const std::string& filename) {
    QString qfilename = QString::fromStdString(filename);

    QPixmap pixmap(qfilename);

    if (pixmap.isNull()) {
        image_holder.setText("Ошибка загрузки изображения");
    } else {

        QSize labelSize = image_holder.size();

        //pixmap = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::FastTransformation);

        image_holder.setPixmap(pixmap);
    }

}
