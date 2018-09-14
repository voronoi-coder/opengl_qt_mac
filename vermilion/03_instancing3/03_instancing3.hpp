//
// Created by zhaojunhe on 2018/9/14.
//
#pragma once

#include <QOpenGLWidget>
#include "../../lib/vbm/vbm.hpp"

class Instancing3Widget : public QOpenGLWidget {
Q_OBJECT
public:
    Instancing3Widget(QWidget *parent = 0);

    ~Instancing3Widget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    GLuint program;

    GLuint color_buffer;
    GLuint model_matrix_buffer;
    GLuint color_tbo;
    GLuint model_matrix_tbo;

    GLint view_matrix_loc;
    GLint projection_matrix_loc;

    float aspect;

    VBObject object;

    QTimer *timer;
};
