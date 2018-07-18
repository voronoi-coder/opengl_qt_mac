//
// Created by zhaojunhe on 2018/7/5.
//

#include "drawcommandswidget.hpp"
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

const char *vsrc = R"SHADER(
uniform mat4 model_matrix;
uniform mat4 projection_matrix;

attribute vec4 position;
attribute vec4 color;

varying vec4 vs_fs_color;

void main(void) {
    vs_fs_color = color;
    gl_Position = projection_matrix * (model_matrix * position);
}
)SHADER";

const char *fsrc = R"SHADER(
varying vec4 vs_fs_color;

void main() {
    gl_FragColor = vs_fs_color;
}

)SHADER";

DrawComWidget::DrawComWidget(QWidget *parent) : QOpenGLWidget(parent) {}

DrawComWidget::~DrawComWidget() {
    makeCurrent();

    vboPos->destroy();
    vboColor->destroy();
    ibo->destroy();
    m_vao->destroy();

    delete m_vao;
    delete ibo;
    delete vboColor;
    delete vboPos;
    delete program;

    doneCurrent();
}


void DrawComWidget::initializeGL() {
    initializeOpenGLFunctions();

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);
    program->bindAttributeLocation("position", 0);
    program->bindAttributeLocation("color", 1);
    program->link();
    program->bind();

    render_model_matrix_loc = program->uniformLocation("model_matrix");
    render_projection_matrix_loc = program->uniformLocation("projection_matrix");

    static const GLfloat vertex_positions[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f
    };

    static const GLfloat vertex_colors[] = {
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f
    };

    static const GLushort vertex_indices[] = {
            0, 1, 2
    };

    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ibo->create();
    ibo->bind();
    ibo->allocate(vertex_indices, sizeof(vertex_indices));

    m_vao = new QOpenGLVertexArrayObject;
    m_vao->create();
    QOpenGLVertexArrayObject::Binder valBinder(m_vao);

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    vboPos = new QOpenGLBuffer;
    vboPos->create();
    vboPos->bind();
    vboPos->allocate(vertex_positions, sizeof(vertex_positions));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    vboPos->release();

    vboColor = new QOpenGLBuffer;
    vboColor->create();
    vboColor->bind();
    vboColor->allocate(vertex_colors, sizeof(vertex_colors));
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    vboColor->release();
}

void DrawComWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    aspect = float(w) / float(h);
}

// TODO nothing in the first two "paintGL"; the default Camera Coordinate :
//                                          1,(0,0,0)
//                                          2,up--the positive Y axis to--the negative Z axis
//                                          3,unit is the same as the world coordinate's.
void DrawComWidget::paintGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    QOpenGLVertexArrayObject::Binder vaoBinder(m_vao);

    program->bind();

    QMatrix4x4 projM;
    projM.setToIdentity();
    projM.perspective(45.0f, aspect, 1.0f, 500.0f);
    QMatrix4x4 modelM;
    modelM.setToIdentity();
    modelM.translate(-3.0f, 0.0f, -5.0f);

    program->setUniformValue(render_projection_matrix_loc, projM);
    program->setUniformValue(render_model_matrix_loc, modelM);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    modelM.setToIdentity();
    modelM.translate(-1.0f, 0.0f, -5.0f);
    program->setUniformValue(render_model_matrix_loc, modelM);
    ibo->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
}

void DrawComWidget::mouseReleaseEvent(QMouseEvent *event) {
    update();
}