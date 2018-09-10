//
// Created by zhaojunhe on 2018/7/9.
//

#include <QWidget>
#include <QGridLayout>
#include "mainwindow.hpp"
#include "glwidget.hpp"

MainWindow::MainWindow() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    for (int i = 0; i < 4; ++i) {
        widgets[i] = new GLWidget;
    }
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(widgets[0], 0, 0);
    mainLayout->addWidget(widgets[1], 1, 0);
    mainLayout->addWidget(widgets[2], 0, 1);
    mainLayout->addWidget(widgets[3], 1, 1);

//    mainLayout->setMargin(2);
//    mainLayout->setSpacing(2);

    widget->setLayout(mainLayout);
}

MainWindow::~MainWindow() {

}