//
// Created by zhaojunhe on 2018/9/27.
//

#include <QMatrix4x4>
#include <array>
#include <iostream>
#include "outlinewidget.hpp"
#include "../../lib/loadshader/LoadShader.hpp"

OutlineGLWidget::OutlineGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

OutlineGLWidget::~OutlineGLWidget() {

}

void OutlineGLWidget::initializeGL() {
    ShaderInfo light_shaders[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/mapbox/outline/vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/mapbox/outline/fs.glsl"},
            {GL_NONE}
    };

    program = LoadShaders(light_shaders);

    matrixLoc = glGetUniformLocation(program, "u_matrix");
    screenSizeLoc = glGetUniformLocation(program, "u_screen");
    outlineColorLoc = glGetUniformLocation(program, "u_outline_color");

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat data[] = {
            -300.0f, -100.0f,
            300.0f, 100.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

    pixelRatio = devicePixelRatioF();
}

void OutlineGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w * pixelRatio, h * pixelRatio);
    std::cout<<"w, h "<<w<<" "<<h<<"\n";
    width = w * pixelRatio;
    height = h * pixelRatio;
}

void OutlineGLWidget::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBindVertexArray(vao);

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.frustum(-1.0f, 1.0f, -height / width, height / width, 1.0f, 5000.0f);
    matrix.translate(0.0f, 0.0f, -500.0f);

    glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, matrix.data());

    GLfloat screenSize[] = {width, height};
    glUniform2fv(screenSizeLoc, 1, screenSize);

    GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glUniform4fv(outlineColorLoc, 1, color);

    GLfloat lineWidthRange[2] = {0.0f, 0.0f};
    glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);

    glLineWidth(7.0f); // not work in OpenGL

    glDrawArrays(GL_LINES, 0, 2);
}
