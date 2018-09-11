//
// Created by zhaojunhe on 2018/7/5.
//
#pragma once

#include <QOpenGLWidget>

class DrawComWidget : public QOpenGLWidget {
public:
    DrawComWidget(QWidget *parent = 0);

    ~DrawComWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:

    float aspect;

    GLenum polygonMode = GL_FILL;

    GLuint program;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];

    GLint model_matrix_loc;
    GLint project_matrix_loc;
};

