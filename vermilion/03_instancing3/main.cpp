//
// Created by zhaojunhe on 2018/9/14.
//
#include <QApplication>
#include <QSurfaceFormat>
#include "03_instancing3.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("03_instancing3");

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    Instancing3Widget widget;
    widget.show();

    return app.exec();
}