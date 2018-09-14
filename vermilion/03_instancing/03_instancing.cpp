//
// Created by zhaojunhe on 2018/9/14.
//

#include <array>
#include <math.h>
#include <iostream>
#include <QMatrix4x4>
#include <QTimer>
#include <QDateTime>
#include "03_instancing.hpp"
#include "../../lib/loadshader/LoadShader.hpp"
#include "../../lib/vmath.h"

#define INSTANCE_COUNT 10

InstancingWidget::InstancingWidget(QWidget *parent) : QOpenGLWidget(parent) {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

InstancingWidget::~InstancingWidget() {

}

void InstancingWidget::initializeGL() {
    ShaderInfo shaderInfo[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing/vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing/fs.glsl"},
            {GL_NONE, NULL}
    };
    program = LoadShaders(shaderInfo);
    glUseProgram(program);

    modelMLoc = glGetUniformLocation(program, "model_matrix");
    projectionMLoc = glGetUniformLocation(program, "projection_matrix");

    object.LoadFromVBM("/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing/armadillo_low.vbm", 0, 1,
                       2);
    object.BindVertexArray();

//    std::array<std::array<float, 4>, INSTANCE_COUNT> colors;
    vmath::vec4 colors[INSTANCE_COUNT];

    for (int n = 0; n < INSTANCE_COUNT; n++) {
        float a = float(n) / 4.0f;
        float b = float(n) / 5.0f;
        float c = float(n) / 6.0f;

        colors[n][0] = 0.5f * (sinf(a + 1.0f) + 1.0f);
        colors[n][1] = 0.5f * (sinf(b + 2.0f) + 1.0f);
        colors[n][2] = 0.5f * (sinf(c + 3.0f) + 1.0f);
        colors[n][3] = 1.0f;
    }

    glGenBuffers(1, &weight_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, weight_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
    std::cout << "sizeof(colors) " << sizeof(colors) << std::endl;

    glVertexAttribDivisor(3, 1);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribDivisor(4, 1);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);
}

void InstancingWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    aspect = float(h) / float(w);
}

void InstancingWidget::paintGL() {
    timer->start(1000);
    float t = float(QDateTime::currentDateTime().toTime_t() & 0x000000FF) / float(0x000000FF);

    int n;
    // Set weights for each instance
    vmath::vec4 weights[INSTANCE_COUNT];

    for (n = 0; n < INSTANCE_COUNT; n++) {
        float a = float(n) / 4.0f;
        float b = float(n) / 5.0f;
        float c = float(n) / 6.0f;

        weights[n][0] = 0.5f * (sinf(t * 6.28318531f * 8.0f + a) + 1.0f);
        weights[n][1] = 0.5f * (sinf(t * 6.28318531f * 26.0f + b) + 1.0f);
        weights[n][2] = 0.5f * (sinf(t * 6.28318531f * 21.0f + c) + 1.0f);
        weights[n][3] = 0.5f * (sinf(t * 6.28318531f * 13.0f + a + b) + 1.0f);
    }

    glBindBuffer(GL_ARRAY_BUFFER, weight_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(weights), weights, GL_DYNAMIC_DRAW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glUseProgram(program);

    // Set four model matrices
    vmath::mat4 model_matrix[4];

    for (n = 0; n < 4; n++) {
        model_matrix[n] = (vmath::scale(5.0f) *
                           vmath::rotate(t * 360.0f * 40.0f + float(n + 1) * 29.0f, 0.0f, 1.0f, 0.0f) *
                           vmath::rotate(t * 360.0f * 20.0f + float(n + 1) * 35.0f, 0.0f, 0.0f, 1.0f) *
                           vmath::rotate(t * 360.0f * 30.0f + float(n + 1) * 67.0f, 0.0f, 1.0f, 0.0f) *
                           vmath::translate((float) n * 10.0f - 15.0f, 0.0f, 0.0f) *
                           vmath::scale(0.01f));
    }

    glUniformMatrix4fv(modelMLoc, 4, GL_FALSE, model_matrix[0]);

    QMatrix4x4 projection_matrix;
    projection_matrix.setToIdentity();
    projection_matrix.frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f);
    projection_matrix.translate(0.0f, 0.0f, -100.0f);

    glUniformMatrix4fv(projectionMLoc, 1, GL_FALSE, projection_matrix.data());

    object.Render(0, INSTANCE_COUNT);
}

void InstancingWidget::keyPressEvent(QKeyEvent *event) {
}