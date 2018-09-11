//
// Created by zhaojunhe on 2018/7/5.
//

#include <QApplication>
#include "03_drawcommands.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("03_drawcommands");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    DrawComWidget drawComWidget;
    drawComWidget.show();

    return app.exec();
}
