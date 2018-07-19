//
// Created by zhaojunhe on 2018/7/18.
//

#include <QKeyEvent>

#include "glwidget.hpp"

#define BUFFER_OFFSET(a) ((void*)(a))

const char *vsrc = R"SHADER(
#version 400 core

layout(location = 0) in vec4 vPosition;

void main(){
    gl_Position = vPosition;
}
)SHADER";

const char *fsrc = R"SHADER(
#version 400 core

out vec4 fColor;

void main(){
    fColor = vec4(0.0, 0.0, 1.0, 1.0);
}
)SHADER";

static void attachShaderSource(GLuint prog, GLenum type, const char *source) {
    GLuint sh;
    sh = glCreateShader(type);
    glShaderSource(sh, 1, &source, nullptr);
    glCompileShader(sh);

    char buffer[4094];
    glGetShaderInfoLog(sh, sizeof(buffer), nullptr, buffer);
    if (strlen(buffer)) {
        throw std::runtime_error(buffer);
    }

    glAttachShader(prog, sh);
    glDeleteShader(sh);
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {
    makeCurrent();
    doneCurrent();
}

void GLWidget::initializeGL() {
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[NumVertices][2] = {
            {-0.90f, -0.90f},
            {0.85f,  -0.90f},
            {-0.90f, 0.85f},  // Triangle 1
            {0.90f,  -0.85f},
            {0.90f,  0.90f},
            {-0.85f, 0.90f}   // Triangle 2
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    GLuint program = glCreateProgram();

    attachShaderSource(program, GL_VERTEX_SHADER, vsrc);
    attachShaderSource(program, GL_FRAGMENT_SHADER, fsrc);

    glLinkProgram(program);
    glUseProgram(program);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_M: {
            polygonMode = (polygonMode == GL_FILL) ? GL_LINE : GL_FILL;
            update();
        }
            break;
    }
}