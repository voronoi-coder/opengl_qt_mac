#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *agrv[]) {
    QApplication app(argc, agrv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}