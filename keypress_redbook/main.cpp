//
// Created by zhaojunhe on 2018/7/18.
//

#include <QApplication>
#include <QSurfaceFormat>
#include "glwidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(4, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("keypress");

    GLWidget glWidget;
    glWidget.show();

    return app.exec();
}