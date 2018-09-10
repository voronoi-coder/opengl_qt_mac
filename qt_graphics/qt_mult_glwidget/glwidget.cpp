//
// Created by zhaojunhe on 2018/7/9.
//

#include "glwidget.hpp"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GLWidget::~GLWidget() {
    makeCurrent();
    doneCurrent();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
    update();
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}