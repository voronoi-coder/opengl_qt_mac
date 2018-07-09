//
// Created by zhaojunhe on 2018/7/9.
//

#include <QApplication>
#include "mainwindow.hpp"
#include "mainwindow2.hpp"
#include "calculator.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

//    MainWindow2 mainWindow2;
//    mainWindow2.show();

//    Calculator calc;
//    calc.show();

    return app.exec();
}
