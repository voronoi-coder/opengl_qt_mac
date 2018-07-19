//
// Created by zhaojunhe on 2018/7/18.
//

#pragma once

#include <QOpenGLWidget>

class QOpenGLShaderProgram;

class GLWidget : public QOpenGLWidget {
public:
    explicit GLWidget(QWidget *parent = 0);

    ~GLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:

    enum VAO_IDs { Triangles, NumVAOs };
    enum Buffer_IDs { ArrayBuffer, NumBuffers };
    enum Attrib_IDs { vPosition = 0 };

    GLuint  VAOs[NumVAOs];
    GLuint  Buffers[NumBuffers];

    static constexpr GLuint NumVertices = 6;

    GLenum polygonMode = GL_FILL;
};
