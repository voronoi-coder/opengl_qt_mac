//
// Created by zhaojunhe on 2018/9/27.
//

#include <QApplication>
#include <QSurfaceFormat>

#include "outlinewidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("outline");

    OutlineGLWidget widget;
    widget.show();

    return app.exec();
}