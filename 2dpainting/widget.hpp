//
// Created by zhaojunhe on 2018/6/21.
//
#pragma once

#include <QWidget>

class Helper;

class Widget : public QWidget {
Q_OBJECT
public:
    Widget(Helper *helper, QWidget *parent);

public slots:

    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *helper;
    int elapsed;
};
