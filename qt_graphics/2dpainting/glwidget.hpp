//
// Created by zhaojunhe on 2018/6/21.
//
#pragma once

#include <QOpenGLWidget>

class Helper;

class GLWidget : public QOpenGLWidget {
Q_OBJECT
public:
    GLWidget(Helper *helper, QWidget *parent);

public slots:

    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *helper;
    int elapsed;
};
