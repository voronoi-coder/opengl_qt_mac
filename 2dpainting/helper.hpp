//
// Created by zhaojunhe on 2018/6/21.
//
#pragma once

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPaintEvent>

class Helper{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};
