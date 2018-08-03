//
// Created by zhaojunhe on 2018/8/3.
//
#pragma once

#ifdef __APPLE__

#include <OpenGL/OpenGL.h>

#endif

#define _DEBUG

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GLenum type;
    const char *filename;
    GLuint shader;
} ShaderInfo;

GLuint LoadShaders(ShaderInfo *);


#ifdef __cplusplus
};
#endif
