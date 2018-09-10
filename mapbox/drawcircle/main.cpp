#include <QApplication>
#include <QSurfaceFormat>
#include "glwidget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("circle");

    GLWidget glWidget;
    glWidget.show();

    return app.exec();
}