//
// Created by zhaojunhe on 2018/9/14.
//
#include <QTimer>
#include <QDateTime>
#include "03_instancing3.hpp"
#include "../../lib/loadshader/LoadShader.hpp"
#include "../../lib/vmath.h"

using namespace vmath;

#define INSTANCE_COUNT 100

Instancing3Widget::Instancing3Widget(QWidget *parent) : QOpenGLWidget(parent) {
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

Instancing3Widget::~Instancing3Widget() {

}

void Instancing3Widget::initializeGL() {
    int n = 0;

    ShaderInfo shaderInfo[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing3/vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing3/fs.glsl"},
            {GL_NONE, NULL}
    };
    program = LoadShaders(shaderInfo);
    glUseProgram(program);

    view_matrix_loc = glGetUniformLocation(program, "view_matrix");
    projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");

    // Set up the TBO samplers
    GLint color_tbo_loc = glGetUniformLocation(program, "color_tbo");
    GLint model_matrix_tbo_loc = glGetUniformLocation(program, "model_matrix_tbo");

    glUniform1i(color_tbo_loc, 0);
    glUniform1i(model_matrix_tbo_loc, 1);

    object.LoadFromVBM("/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing2/armadillo_low.vbm", 0, 1,
                       2);

    glGenTextures(1, &color_tbo);
    glBindTexture(GL_TEXTURE_BUFFER, color_tbo);

    // Generate the colors of the objects
    vec4 colors[INSTANCE_COUNT];

    for (n = 0; n < INSTANCE_COUNT; n++) {
        float a = float(n) / 4.0f;
        float b = float(n) / 5.0f;
        float c = float(n) / 6.0f;

        colors[n][0] = 0.5f + 0.25f * (sinf(a + 1.0f) + 1.0f);
        colors[n][1] = 0.5f + 0.25f * (sinf(b + 2.0f) + 1.0f);
        colors[n][2] = 0.5f + 0.25f * (sinf(c + 3.0f) + 1.0f);
        colors[n][3] = 1.0f;
    }

    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, color_buffer);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, color_buffer);

    glGenTextures(1, &model_matrix_tbo);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, model_matrix_tbo);
    glGenBuffers(1, &model_matrix_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, model_matrix_buffer);
    glBufferData(GL_TEXTURE_BUFFER, INSTANCE_COUNT * sizeof(mat4), NULL, GL_DYNAMIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, model_matrix_buffer);
    glActiveTexture(GL_TEXTURE0);
}

void Instancing3Widget::resizeGL(int w, int h) {
    glViewport(0, 0 , w, h);

    aspect = float(h) / float(w);
}

void Instancing3Widget::paintGL() {
    timer->start(1000);
    float t = float(QDateTime::currentDateTime().toTime_t() & 0x000000FF) / float(0x000000FF);

    int n = 0;
    // Set model matrices for each instance
    mat4 matrices[INSTANCE_COUNT];

    for (n = 0; n < INSTANCE_COUNT; n++)
    {
        float a = 50.0f * float(n) / 4.0f;
        float b = 50.0f * float(n) / 5.0f;
        float c = 50.0f * float(n) / 6.0f;

        matrices[n] = vmath::rotate(a + t * 360.0f, 1.0f, 0.0f, 0.0f) *
                      vmath::rotate(b + t * 360.0f, 0.0f, 1.0f, 0.0f) *
                      vmath::rotate(c + t * 360.0f, 0.0f, 0.0f, 1.0f) *
                      vmath::translate(10.0f + a, 40.0f + b, 50.0f + c);
    }

    // Bind the weight VBO and change its data
    glBindBuffer(GL_TEXTURE_BUFFER, model_matrix_buffer);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(matrices), matrices, GL_DYNAMIC_DRAW);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Activate instancing program
    glUseProgram(program);

    // Set up the view and projection matrices
    mat4 view_matrix(vmath::translate(0.0f, 0.0f, -1500.0f) * vmath::rotate(t * 360.0f * 2.0f, 0.0f, 1.0f, 0.0f));
    mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f));

    glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, view_matrix);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);

    // Render INSTANCE_COUNT objects
    object.Render(0, INSTANCE_COUNT);
}
