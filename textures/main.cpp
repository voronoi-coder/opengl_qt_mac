//
// Created by zhaojunhe on 2018/6/19.
//
#include <QApplication>
#include <QSurfaceFormat>

#include "windows.hpp"

int main(int argc, char *argv[]){
    Q_INIT_RESOURCE(textures);

    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Window window;
    window.show();

    return app.exec();
}

