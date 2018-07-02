//
// Created by zhaojunhe on 2018/7/2.
//

#include <QOpenGLShaderProgram>
#include "glwidget.hpp"

const char *vsrc = R"SHADER(
attribute highp vec4 vertex;

void main()
{
    gl_Position = vertex;
}
)SHADER";

const char *fsrc = R"SHADER(

void main()
{
    gl_FragColor = vec4( 0.0, 0.0, 1.0, 1.0 );
}
)SHADER";

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), program(0) {}

GLWidget::~GLWidget() {
    makeCurrent();
    vbo.destroy();
    delete program;
    doneCurrent();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
    update();
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    GLfloat vertices[NumVertices][2] = {
            {-0.9f,  -0.9f},
            {0.85f,  -0.9f},
            {-0.9,   0.85}, // Triangle 1
            {0.9f,   -0.85f},
            {0.9f,   0.9f},
            {-0.85f, 0.9f}  // Triangel 2
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fsrc);
    program->bindAttributeLocation("vertex", 0);
    program->link();
    program->bind();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vbo.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));

    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}


