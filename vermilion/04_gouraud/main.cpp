//
// Created by zhaojunhe on 2018/8/9.
//

#include <QApplication>
#include <QSurfaceFormat>
#include "04_gourand.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(4, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Gouraud (Float) Example");

    GouraudFloatGLWidget widget;
    widget.show();

    return app.exec();
}