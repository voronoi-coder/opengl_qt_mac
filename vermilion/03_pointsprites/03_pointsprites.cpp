//
// Created by zhaojunhe on 2018/9/18.
//
#include <QTimer>
#include <QDateTime>
#include <iostream>

#include "03_pointsprites.hpp"
#include "../../lib/loadshader/LoadShader.hpp"
#include "../../lib/vmath.h"

using namespace vmath;

#define POINT_COUNT 4

static void checkGLError(const char *cmd) {
    int error = glGetError();
    std::string err;
    if (error != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_ENUM:
                err = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                err = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                err = "GL_INVALID_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                err = "GL_OUT_OF_MEMORY";
                break;
            default:
                err = "unknow error";
                break;
        }
        printf("%s error=%s(%d)\n", cmd, err.c_str(), error);
    };
}

namespace vtarga {
unsigned char *load_targa(const char *filename, GLenum &format, int &width, int &height);
};

static inline float random_float() {
    float res;
    unsigned int tmp;
    static unsigned int seed = 0x13371337;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

PointSpritesWidget::PointSpritesWidget(QWidget *parent) : QOpenGLWidget(parent) {
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

PointSpritesWidget::~PointSpritesWidget() {
}

void PointSpritesWidget::initializeGL() {
    GLenum format = GL_RGBA;
    int width = 128, height = 128;
    uint8_t *data = NULL;

    glGenTextures(1, &sprite_texture);
    checkGLError("glGenTextures");
    glBindTexture(GL_TEXTURE_2D, sprite_texture);
    checkGLError("glBindTexture");
    data = vtarga::load_targa("/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_pointsprites/sprite2.tga",
                              format, width, height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    delete[] data;

    glGenerateMipmap(GL_TEXTURE_2D);
    checkGLError("glGenerateMipmap");

    static ShaderInfo shader_info[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_pointsprites/vs.glsl", 0},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/03_pointsprites/fs.glsl", 0},
            {GL_NONE, NULL,                                                                                       0}
    };
    program = LoadShaders(shader_info);
    glUseProgram(program);

    model_matrix_loc = glGetUniformLocation(program, "model_matrix");
    // debug "project_matrix" -> "projection_matrix"
    projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");

    // A single triangle
    static vec4 *vertex_positions;

    // Set up the vertex attributes
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, POINT_COUNT * sizeof(vec4), NULL, GL_STATIC_DRAW);

    vertex_positions = (vec4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    for (int n = 0; n < POINT_COUNT; n++) {
        vertex_positions[n] = vec4(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f,
                                   random_float() * 2.0f - 1.0f, 1.0f);
//        std::cout << "vertex " << n << " : " << vertex_positions[n][0] << " " << vertex_positions[n][1] << " "
//                  << vertex_positions[n][2]
//                  << " " << vertex_positions[n][3] << " " << std::endl;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void PointSpritesWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    aspect = float(height) / float(width);
}

void PointSpritesWidget::paintGL() {
    timer->start(1000);
    float t = float(QDateTime::currentDateTime().toTime_t() & 0x000000FF) / float(0x000000FF);

    static const vec3 X(1.0f, 0.0f, 0.0f);
    static const vec3 Y(0.0f, 1.0f, 0.0f);
    static const vec3 Z(0.0f, 0.0f, 1.0f);

    // Setup
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate simple shading program
    glUseProgram(program);
    
    // Set up the model and projection matrix
    mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 8.0f));
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);

    mat4 model_matrix;
    model_matrix = translate(0.0f, 0.0f, -2.0f) *
                   rotate(t * 360.0f, Y) * rotate(t * 720.0f, Z);
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, model_matrix);

    glBindTexture(GL_TEXTURE_2D, sprite_texture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_PROGRAM_POINT_SIZE);
//    glPointSize(32.0f);

    glDrawArrays(GL_POINTS, 0, POINT_COUNT);
}
