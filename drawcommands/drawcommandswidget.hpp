//
// Created by zhaojunhe on 2018/7/5.
//
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

class DrawComWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    DrawComWidget(QWidget *parent = 0);

    ~DrawComWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event)override;
private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer *vboPos;
    QOpenGLBuffer *vboColor;
    QOpenGLBuffer *ibo;
    QOpenGLVertexArrayObject *m_vao;

    int render_model_matrix_loc;
    int render_projection_matrix_loc;

    float aspect;

    GLenum polygonMode = GL_FILL;
};

