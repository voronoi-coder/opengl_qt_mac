//
// Created by zhaojunhe on 2018/9/4.
//

#include <iostream>
#include <QApplication>
#include <QSurfaceFormat>

#include "clipplanewidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("clip_plane");

    ClipPlaneWidget widget;
    widget.show();

    return app.exec();
}

