//
// Created by zhaojunhe on 2018/8/20.
//
#include <QApplication>
#include <QSurfaceFormat>
#include "06_statictexture.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("static_texture");

    StaticTextureGLWidget widget;
    widget.show();

    return app.exec();
}

