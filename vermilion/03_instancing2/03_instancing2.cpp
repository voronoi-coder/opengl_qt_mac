//
// Created by zhaojunhe on 2018/9/14.
//

#include <QDateTime>
#include <QTimer>
#include "03_instancing2.hpp"
#include "../../lib/loadshader/LoadShader.hpp"
#include "../../lib/vmath.h"

using namespace vmath;

#define INSTANCE_COUNT 100

Instancing2Widget::Instancing2Widget(QWidget *parent) {
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

Instancing2Widget::~Instancing2Widget() {
    glUseProgram(0);
    glDeleteProgram(program);
    glDeleteBuffers(1, &color_vbo);
    glDeleteBuffers(1, &model_matrix_buffer);
}

void Instancing2Widget::initializeGL() {
    int n = 0;

    ShaderInfo shaderInfo[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing2/vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing2/fs.glsl"},
            {GL_NONE, NULL}
    };
    program = LoadShaders(shaderInfo);
    glUseProgram(program);

    view_matrix_loc = glGetUniformLocation(program, "view_matrix");
    projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");

    object.LoadFromVBM("/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_instancing2/armadillo_low.vbm", 0, 1,
                       2);
    object.BindVertexArray();

    int position_loc = glGetAttribLocation(program, "position");
    int normal_loc = glGetAttribLocation(program, "normal");
    int color_loc = glGetAttribLocation(program, "color");
    int matrix_loc = glGetAttribLocation(program, "model_matrix");

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

    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);

    // Now we set up the color array. We want each instance of our geometry
    // to assume a different color, so we'll just pack colors into a buffer
    // object and make an instanced vertex attribute out of it.
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(color_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(color_loc);
    // This is the important bit... set the divisor for the color array to
    // 1 to get OpenGL to give us a new value of 'color' per-instance
    // rather than per-vertex.
    glVertexAttribDivisor(color_loc, 1);

    glGenBuffers(1, &model_matrix_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, model_matrix_buffer);
    glBufferData(GL_ARRAY_BUFFER, INSTANCE_COUNT * sizeof(mat4), NULL, GL_DYNAMIC_DRAW);
    // Loop over each column of the matrix...
    for (int i = 0; i < 4; i++) {
        // Set up the vertex attribute
        glVertexAttribPointer(matrix_loc + i,              // Location
                              4, GL_FLOAT, GL_FALSE,       // vec4
                              sizeof(mat4),                // Stride
                              (void *) (sizeof(vec4) * i)); // Start offset
        // Enable it
        glEnableVertexAttribArray(matrix_loc + i);
        // Make it instanced
        glVertexAttribDivisor(matrix_loc + i, 1);
    }

    // Done (unbind the object's VAO)
    glBindVertexArray(0);
}

void Instancing2Widget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    aspect = (float) h / (float) w;
}

void Instancing2Widget::paintGL() {
    timer->start(1000);
    float t = float(QDateTime::currentDateTime().toTime_t() & 0x000000FF) / float(0x000000FF);

    int n;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Bind the weight VBO and change its data
    glBindBuffer(GL_ARRAY_BUFFER, model_matrix_buffer);

    mat4 *matrices = (mat4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (n = 0; n < INSTANCE_COUNT; n++) {
        float a = 50.0f * float(n) / 4.0f;
        float b = 50.0f * float(n) / 5.0f;
        float c = 50.0f * float(n) / 6.0f;

        matrices[n] = rotate(a + t * 360.0f, 1.0f, 0.0f, 0.0f) *
                      rotate(b + t * 360.0f, 0.0f, 1.0f, 0.0f) *
                      rotate(c + t * 360.0f, 0.0f, 0.0f, 1.0f) *
                      translate(10.0f + a, 40.0f + b, 50.0f + c);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    glUseProgram(program);
    mat4 view_matrix(translate(0.0f, 0.0f, -1500.0f) * rotate(t * 360.0f * 2.0f, 0.0f, 1.0f, 0.0f));
    mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f));

    glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, view_matrix);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);

    object.Render(0, INSTANCE_COUNT);
}
