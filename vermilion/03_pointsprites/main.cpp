//
// Created by zhaojunhe on 2018/9/18.
//
#include <QApplication>
#include <QSurfaceFormat>

#include "03_pointsprites.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    PointSpritesWidget widget;
    widget.show();

    return app.exec();
}
