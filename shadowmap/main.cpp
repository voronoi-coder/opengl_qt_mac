//
// Created by zhaojunhe on 2018/8/10.
//
#include <QApplication>
#include <QSurfaceFormat>
#include "shadowmapwidget.hpp"

// The drawing is not successful.

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(32);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Shadow Mapping Example");

    ShadowMapGLWidget widget;
    widget.show();

    return app.exec();
}