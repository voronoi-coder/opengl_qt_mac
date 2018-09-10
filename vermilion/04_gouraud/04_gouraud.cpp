//
// Created by zhaojunhe on 2018/8/9.
//

#include <iostream>
#include <QKeyEvent>
#include "04_gourand.hpp"
#include "../../lib/loadshader/LoadShader.hpp"

#define BUFFER_OFFSET(a) ((void*)(a))

GouraudFloatGLWidget::GouraudFloatGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
}

GouraudFloatGLWidget::~GouraudFloatGLWidget() {
    makeCurrent();
    doneCurrent();
}

void GouraudFloatGLWidget::initializeGL() {
    std::cout<<__FUNCTION__<<std::endl;
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    struct VertexData{
        GLubyte color[4];
        GLfloat position[4];
    };

    VertexData vertices[NumVertices] = {
            {{ 255,   0,   0, 255 }, { -0.90f, -0.90f }},  // Triangle 1
            {{   0, 255,   0, 255 }, {  0.85f, -0.90f }},
            {{   0,   0, 255, 255 }, { -0.90f,  0.85f }},
            {{  10,  10,  10, 255 }, {  0.90f, -0.85f }},  // Triangle 2
            {{ 100, 100, 100, 255 }, {  0.90f,  0.90f }},
            {{ 255, 255, 255, 255 }, { -0.85f,  0.90f }}
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/04_gouraud/vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/04_gouraud/fs.glsl"},
            {GL_NONE, NULL}
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    heightLoc = glGetUniformLocation(program, "u_height");

    glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].color)));

    glEnableVertexAttribArray(vColor);
    glEnableVertexAttribArray(vPosition);
}

void GouraudFloatGLWidget::resizeGL(int w, int h) {
    std::cout<<__FUNCTION__<<std::endl;
    glViewport(0,0,w,h);
}

void GouraudFloatGLWidget::paintGL() {
    std::cout<<__FUNCTION__<<std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glUniform1f(heightLoc, 200.0);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void GouraudFloatGLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_M: {
            polygonMode = (polygonMode == GL_FILL) ? GL_LINE : GL_FILL;
            update();
        }
            break;
    }
}