//
// Created by zhaojunhe on 2018/8/20.
//
#pragma once

#include <QOpenGLWidget>

class StaticTextureGLWidget : public QOpenGLWidget {
public:
    StaticTextureGLWidget(QWidget *parent = 0);

    ~StaticTextureGLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    float aspect;
    GLuint base_prog;
    GLuint vao;
    GLuint quad_vbo;
    GLuint tex;
    GLint texLoc;
};
