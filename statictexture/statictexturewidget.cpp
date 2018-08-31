//
// Created by zhaojunhe on 2018/8/20.
//

#include "statictexturewidget.hpp"
#include "../loadshader/LoadShader.hpp"
#include <gl3ext.h>

StaticTextureGLWidget::StaticTextureGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

StaticTextureGLWidget::~StaticTextureGLWidget() {
    glUseProgram(0);
    glDeleteProgram(base_prog);
    glDeleteTextures(1, &tex);
    glDeleteVertexArrays(1, &vao);
}

void StaticTextureGLWidget::initializeGL() {
    ShaderInfo light_shaders[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/statictexture/static_texture_vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/statictexture/static_texture_fs.glsl"},
            {GL_NONE}
    };

    base_prog = LoadShaders(light_shaders);
    texLoc = glGetUniformLocation(base_prog, "tex");

    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);

    static const GLfloat quad_data[] = {
            0.75f, -0.75f,
            -0.75f, -0.75f,
            -0.75f, 0.75f,
            0.75f, 0.75f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) (8 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, 8, 8);

    static const unsigned char texture_data[] = {
            0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
            0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
            0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
            0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
            0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
    };

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE, texture_data);

    static const GLint swizzles[] = {GL_RED, GL_RED, GL_RED, GL_ONE};
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzles);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_2D);
}

void StaticTextureGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    aspect = float(h) / float(w);
}

void StaticTextureGLWidget::paintGL() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_CULL_FACE);
    glUseProgram(base_prog);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
//    glUniform1i(texLoc, 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}