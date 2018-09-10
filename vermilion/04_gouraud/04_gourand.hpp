//
// Created by zhaojunhe on 2018/8/9.
//
#pragma once

#include <QOpenGLWidget>

class QOpenGLShaderProgram;

class GouraudFloatGLWidget : public QOpenGLWidget {
public:
    explicit GouraudFloatGLWidget(QWidget *parent = 0);

    ~GouraudFloatGLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    enum VAO_IDs {Triangles, NumVAOs};
    enum Buffer_IDs{ArrayBuffer, NumBuffers};
    enum Attrib_IDs{vPosition = 0, vColor = 1};

    GLuint VAOs[NumVAOs];
    GLuint Buffers[NumBuffers];

    static constexpr GLuint NumVertices = 6;

    GLenum polygonMode = GL_FILL;

    GLint heightLoc;
};
