//
// Created by zhaojunhe on 2018/9/27.
//

#include <QMatrix4x4>
#include <array>
#include <iostream>
#include <QOpenGLContext>
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
            -300.0f, -100.0f, 100.0f,
            300.0f, 100.0f, 100.0f
    };

    vextexs.clear();

    const int nbSubdivisions = 10;
    const int size = 300;
    if (vextexs.size() <= 0) {
        for (int i = 0; i <= nbSubdivisions; ++i) {
            const float pos = size * (2.0 * i / nbSubdivisions - 1.0);
            vextexs.append(pos);
            vextexs.append(-size);
            vextexs.append(0);
            vextexs.append(pos);
            vextexs.append(+size);
            vextexs.append(0);
            vextexs.append(-size);
            vextexs.append(pos);
            vextexs.append(0);
            vextexs.append(size);
            vextexs.append(pos);
            vextexs.append(0);
        }
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vextexs.size(), vextexs.data(), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

    pixelRatio = devicePixelRatioF();


    const GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
    const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
    const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号

    GLint majVers = 0, minVers = 0, profile = 0, flags = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &majVers);
    glGetIntegerv(GL_MINOR_VERSION, &minVers);
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

    printf("GL_VENDOR : %s\n",name);
    printf("GL_RENDERER : %s\n",biaoshifu);
    printf("GL_VERSION : %s\n",OpenGLVersion);

    printf("GL_MAJOR_VERSION %d\n", majVers);
    printf("GL_MINOR_VERSION %d\n", minVers);
    printf("GL_CONTEXT_PROFILE_MASK %d\n", profile);
    printf("GL_CONTEXT_FLAGS %d\n", flags);

    qDebug()<<context()->isOpenGLES();

    const char *ext = (const char *)glGetString(GL_EXTENSIONS);

    qDebug()<<QString(ext);
}

void OutlineGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w * pixelRatio, h * pixelRatio);
    std::cout << "w, h " << w << " " << h << "\n";
    width = w * pixelRatio;
    height = h * pixelRatio;

}

void OutlineGLWidget::paintGL() {
    glClearColor(249.0f / 255.0f, 245.0f / 255.f, 237.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
//    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(program);

    glBindVertexArray(vao);

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.frustum(-1.0f, 1.0f, -height / width, height / width, 1.0f, 5000.0f);
    matrix.translate(0.0f, 0.0f, -500.0f);
    matrix.rotate(-1.0f, 1.0f, 0.0f, 0.0f);
//    matrix.rotate(-45.0f, 0.0f, 0.0f, 1.0f);

//
    glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, matrix.data());

    GLfloat screenSize[] = {width, height};
    glUniform2fv(screenSizeLoc, 1, screenSize);

    GLfloat color[] = {170.0f / 255.f, 168.f / 255.f, 163.f / 255.f, 1.0f};
    glUniform4fv(outlineColorLoc, 1, color);

    GLfloat lineWidthRange[2] = {0.0f, 0.0f};
    glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);

    glLineWidth(4.0f); // not work in OpenGL

    glDrawArrays(GL_LINES, 0, vextexs.size() / 3);
}
