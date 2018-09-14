//
// Created by zhaojunhe on 2018/9/14.
//

#include <QApplication>
#include <QSurfaceFormat>
#include "03_instancing2.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("03_instancing2");

    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    Instancing2Widget widget;
    widget.show();

    return app.exec();
}