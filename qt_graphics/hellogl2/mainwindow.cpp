//
// Created by zhaojunhe on 2018/6/22.
//

#include "mainwindow.hpp"
#include "window.hpp"
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow() {
    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    connect(addNew, &QAction::triggered, this, &MainWindow::onAddNew);
    setMenuBar(menuBar);

    onAddNew();
}

MainWindow::~MainWindow(){}

void MainWindow::onAddNew() {
    if (!centralWidget())
        setCentralWidget(new Window(this));
    else
        QMessageBox::information(0, tr("Cannot add new window"), tr("Already occupied. Undock first."));
}
