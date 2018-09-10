//
// Created by zhaojunhe on 2018/7/31.
//
#include <QOpenGLShaderProgram>
#include <array>
#include <iostream>

#include "glwidget.hpp"
#include "circle.hpp"

#define COUT(n) std::cout<<#n<<" "<<n<<std::endl

/*
     * @param {number} x vertex position
     * @param {number} y vertex position
     * @param {number} ex extrude normal
     * @param {number} ey extrude normal
     */
std::array<short, 2> sneakIntoExtrude(std::array<short, 2> p, float ex, float ey) {
    return {static_cast<short>((p[0] * 2) + ((ex + 1) / 2)), static_cast<short>((p[1] * 2) + ((ey + 1) / 2))};
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {
    makeCurrent();
    doneCurrent();
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    GLfloat data[] = {
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, -1, -1).at(0)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, -1, -1).at(1)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, 1, -1).at(0)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, 1, -1).at(1)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, 1, 1).at(0)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, 1, 1).at(1)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, -1, 1).at(0)),
            static_cast<GLfloat>(sneakIntoExtrude({0, 0}, -1, 1).at(1))
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(data, sizeof(data));
    std::cout<<"data sizeof "<< sizeof(data)<<std::endl;

    static const GLushort vertex_indices[] = {
            0, 1, 2, 0, 3, 2
    };

    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ibo->create();
    ibo->bind();
    ibo->allocate(vertex_indices, sizeof(vertex_indices));

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, mdgl::shaders::circle::vertexSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, mdgl::shaders::circle::fragmentSource);
    program->bindAttributeLocation("a_pos", 0);
    program->link();
    program->bind();

    m_matrixLoc = program->uniformLocation("u_matrix");
    u_color = program->uniformLocation("u_color");
    u_radius = program->uniformLocation("u_radius");
//    u_scale_with_map = program->uniformLocation("u_scale_with_map");
//    u_pitch_with_map = program->uniformLocation("u_pitch_with_map");
//    u_extrude_scale = program->uniformLocation("u_extrude_scale");
//    u_camera_to_center_distance = program->uniformLocation("u_camera_to_center_distance");
//    u_blur = program->uniformLocation("u_blur");
//    u_opacity = program->uniformLocation("u_opacity");
//    u_stroke_color = program->uniformLocation("u_stroke_color");
//    u_stroke_width = program->uniformLocation("u_stroke_width");
//    u_stroke_opacity = program->uniformLocation("u_stroke_opacity");

}


void GLWidget::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
    aspect = float(w) / float(h);

}

// TODO nothing in the first two "paintGL"; the default Camera Coordinate :
//                                          1,(0,0,0)
//                                          2,up--the positive Y axis to--the negative Z axis
//                                          3,unit is the same as the world coordinate's.

void GLWidget::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int w = size().width();
    int h = size().height();


    QMatrix4x4 projM;
    projM.setToIdentity();
    projM.perspective(45.0f, aspect, 1.0f, 500.0f);
    QMatrix4x4 modelM;
    modelM.setToIdentity();
    modelM.translate(.0f, 0.0f, -5.0f);

    vbo.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(GL_FLOAT));

    program->setUniformValue(m_matrixLoc, projM * modelM);
    program->setUniformValue(u_color, QVector4D{1.0f, 0.0f, 0.0f, 1.0f});
    program->setUniformValue(u_radius, 1.0f);
//    program->setUniformValue(u_scale_with_map, false);
//    program->setUniformValue(u_pitch_with_map, false);
//    program->setUniformValue(u_extrude_scale, 1.0f);
//    program->setUniformValue(u_camera_to_center_distance, 1.0f);
//    program->setUniformValue(u_blur, 0.0f);
//    program->setUniformValue(u_opacity, 1.0f);
//    program->setUniformValue(u_stroke_color, QVector4D{1.0f, 1.0f, 0.0f, 1.0f});
//    program->setUniformValue(u_stroke_width, 2.0f);
//    program->setUniformValue(u_stroke_opacity, 1.0f);

    ibo->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

void GLWidget::keyPressEvent(QKeyEvent *event) {

}