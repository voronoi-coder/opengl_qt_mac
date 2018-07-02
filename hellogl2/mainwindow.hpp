//
// Created by zhaojunhe on 2018/6/22.
//
#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

private slots:

    void onAddNew();
};
