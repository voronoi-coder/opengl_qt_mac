//
// Created by zhaojunhe on 2018/7/18.
//

#include <QApplication>
#include <QSurfaceFormat>
#include "02_uniformblock.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("02_uniformblock");

    GLWidget glWidget;
    glWidget.show();

    return app.exec();
}