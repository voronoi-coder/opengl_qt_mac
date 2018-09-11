//
// Created by zhaojunhe on 2018/7/5.
//

#include "03_drawcommands.hpp"
#include "../../lib/loadshader/LoadShader.hpp"
#include <QDebug>
#include <QKeyEvent>
#include <QMatrix4x4>

DrawComWidget::DrawComWidget(QWidget *parent) : QOpenGLWidget(parent) {}

DrawComWidget::~DrawComWidget() {
    makeCurrent();
    glUseProgram(0);
    glDeleteProgram(program);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
    doneCurrent();
}


void DrawComWidget::initializeGL() {
    ShaderInfo shader_info[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_drawcommands/vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_drawcommands/fs.glsl"},
            {GL_NONE, NULL}
    };

    program = LoadShaders(shader_info);

    glUseProgram(program);
    model_matrix_loc = glGetUniformLocation(program, "model_matrix");
    project_matrix_loc = glGetUniformLocation(program, "projection_matrix");

    static const GLfloat vertex_positions[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 1.0f,
    };

    // Color for each vertex
    static const GLfloat vertex_colors[] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f
    };

    // Indices for the triangle strips
    static const GLushort vertex_indices[] = {
            0, 1, 2
    };

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors) + sizeof(vertex_positions), (void *) 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void DrawComWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    aspect = float(h) / float(w);
}

// TODO nothing in the first two "paintGL"; the default Camera Coordinate :
//                                          1,(0,0,0)
//                                          2,up--the positive Y axis to--the negative Z axis
//                                          3,unit is the same as the world coordinate's.
void DrawComWidget::paintGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_CULL_FACE); // draw counterclockwise triangle, discard clockwise triangle.
    glDisable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    glUseProgram(program);
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

    QMatrix4x4 projMatrix;
    QMatrix4x4 modelMatrix;

    projMatrix.setToIdentity();
    projMatrix.frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f);
    glUniformMatrix4fv(project_matrix_loc, 1, GL_FALSE, projMatrix.data());

    modelMatrix.setToIdentity();
    modelMatrix.translate(-3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, modelMatrix.data());
    glDrawArrays(GL_TRIANGLES, 0, 3);

    modelMatrix.setToIdentity();
    modelMatrix.translate(-1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, modelMatrix.data());
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

    modelMatrix.setToIdentity();
    modelMatrix.translate(1.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, modelMatrix.data());
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1); // color changes.

    modelMatrix.setToIdentity();
    modelMatrix.translate(3.0f, 0.0f, -5.0f);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, modelMatrix.data());
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
}

void DrawComWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_M: {
            polygonMode = (polygonMode == GL_FILL) ? GL_LINE : GL_FILL;
            update();
        }
            break;
    }
}
