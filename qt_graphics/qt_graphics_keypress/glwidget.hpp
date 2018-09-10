//
// Created by zhaojunhe on 2018/7/2.
//
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
class QOpenGLShaderProgram;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    explicit GLWidget(QWidget *parent = 0);

    ~GLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;

    static constexpr GLuint NumVertices = 6;
};
