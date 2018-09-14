//
// Created by zhaojunhe on 2018/9/14.
//
#pragma once

#include <QOpenGLWidget>
#include "../../lib/vbm/vbm.hpp"

class Instancing2Widget : public QOpenGLWidget {
Q_OBJECT
public:
    Instancing2Widget(QWidget *parent = 0);

    ~Instancing2Widget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    GLuint program;
    GLuint model_matrix_buffer;
    GLuint color_vbo;

    GLint view_matrix_loc;
    GLint projection_matrix_loc;

    GLint position_loc;
    GLint normal_loc;
    GLint color_loc;
    GLint matrix_loc;

    float aspect;

    VBObject object;

    QTimer *timer;
};
