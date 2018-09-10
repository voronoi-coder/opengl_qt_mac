//
// Created by zhaojunhe on 2018/7/18.
//

#include <QKeyEvent>
#include <cstdlib>


#include "02_uniformblock.hpp"
#include "../../lib/loadshader/LoadShader.hpp"

#define BUFFER_OFFSET(a) ((void*)(a))

size_t TypeSize(GLenum type) {
    size_t size;
#define CASE(Enum, Count, Type) \
    case Enum:size = Count * sizeof(Type);break

    switch (type) {
        CASE(GL_FLOAT, 1, GLfloat);
        CASE(GL_FLOAT_VEC2, 2, GLfloat);
        CASE(GL_FLOAT_VEC3, 3, GLfloat);
        CASE(GL_FLOAT_VEC4, 4, GLfloat);
        CASE(GL_INT, 1, GLint);
        CASE(GL_INT_VEC2, 2, GLint);
        CASE(GL_INT_VEC3, 3, GLint);
        CASE(GL_INT_VEC4, 4, GLint);
        CASE(GL_UNSIGNED_INT, 1, GLuint);
        CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
        CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
        CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);
        CASE(GL_BOOL, 1, GLboolean);
        CASE(GL_BOOL_VEC2, 2, GLboolean);
        CASE(GL_BOOL_VEC3, 3, GLboolean);
        CASE(GL_BOOL_VEC4, 4, GLboolean);
        CASE(GL_FLOAT_MAT2, 4, GLfloat);
        CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
        CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
        CASE(GL_FLOAT_MAT3, 9, GLfloat);
        CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
        CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
        CASE(GL_FLOAT_MAT4, 16, GLfloat);
        CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
        CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE
        default:
            fprintf(stderr, "Unknown type:0x%x\n", type);
            exit(EXIT_FAILURE);
            break;
    }

    return size;
}


GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {
    makeCurrent();
    doneCurrent();
}

void GLWidget::initializeGL() {
    GLuint program;
    glClearColor(1, 0, 0, 1);
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/02_uniformblock/unifom_block_vs.glsl", vShader},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/vermilion/02_uniformblock/unifom_block_fs.glsl", fShader},
            {GL_NONE, NULL}
    };

    program = LoadShaders(shaders);
    glUseProgram(program);

    GLuint uboIndex;
    GLint uboSize;
    GLuint ubo;
    GLvoid *buffer;

    uboIndex = glGetUniformBlockIndex(program, "Uniforms");
    glGetActiveUniformBlockiv(program, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
    buffer = malloc(uboSize);

    if (buffer == NULL) {
        fprintf(stderr, "Unable to allocate buffer\n");
        exit(EXIT_FAILURE);
    } else {
        enum {
            Translation, Scale, Rotation, Enabled, NumUniforms
        };

        GLfloat scale = 0.5;
        GLfloat translation[] = {0.1, 0.1, 0.0};
        GLfloat rotation[] = {90, 0.0, 0.0, 1.0};
        GLboolean enabled = GL_TRUE;

        const char *names[NumUniforms] = {
                "translation",
                "scale",
                "rotation",
                "enabled"
        };

        GLuint indices[NumUniforms];
        GLint size[NumUniforms];
        GLint offset[NumUniforms];
        GLint type[NumUniforms];
        glGetUniformIndices(program, NumUniforms, names, indices);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_SIZE, size);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_TYPE, type);

        memcpy((char*)buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
        memcpy((char*)buffer + offset[Translation], &translation, size[Translation] * TypeSize(type[Translation]));
        memcpy((char*)buffer + offset[Rotation], &rotation, size[Rotation] * TypeSize(type[Rotation]));
        memcpy((char*)buffer + offset[Enabled], &enabled, size[Enabled] * TypeSize(type[Enabled]));

        glGenBuffers(1, &ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);

        glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);
    }

}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
}
