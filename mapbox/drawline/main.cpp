//
// Created by zhaojunhe on 2018/8/20.
//
#include <QApplication>
#include <QSurfaceFormat>
#include "drawlinewidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("drawline");

    DrawLineGLWidget widget;
    widget.show();

    return app.exec();
}

