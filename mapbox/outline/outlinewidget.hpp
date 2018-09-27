//
// Created by zhaojunhe on 2018/9/27.
//
#pragma once

#include <QOpenGLWidget>

class OutlineGLWidget : public QOpenGLWidget {

public:
    OutlineGLWidget(QWidget *parent = 0);

    ~OutlineGLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    GLuint program;
    GLuint vbo;
    GLuint vao;

    GLint matrixLoc;
    GLint screenSizeLoc;
    GLint outlineColorLoc;

    GLfloat width;
    GLfloat height;
};
