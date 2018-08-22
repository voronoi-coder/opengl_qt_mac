//
// Created by zhaojunhe on 2018/8/18.
//
#pragma once

#ifdef __APPLE__

#include <OpenGL/OpenGL.h>

#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Enough mips for 16K x 16K, which is the minumum required for OpenGL 4.x
#define MAX_TEXTURE_MIPS    14

// Each texture image data structure contains an array of MAX_TEXTURE_MIPS
// of these mipmap structures. The structure represents the mipmap data for
// all slices at that level.
struct vglImageMipData {
    GLsizei width;          // Width of this mipmap level
    GLsizei height;          // Height of this mipmap level
    GLsizei depth;          // Depth of this mipmap level
    GLsizeiptr mipStride;   //  Distance in bytes between mip levels in memory
    GLvoid *data;           // Pointer to data
};

struct vglImageData {
    GLenum target;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
    GLenum swizzle[4];
    GLsizei mipLevels;
    GLsizei slices;
    GLsizeiptr sliceStride;
    GLsizeiptr totalDataSize;
    vglImageMipData mip[MAX_TEXTURE_MIPS];
};

void vglLoadImage(const char *filename, vglImageData *image);
void vglUnloadImage(vglImageData *image);
GLuint vglLoadTexture(const char *filename, GLuint texture, vglImageData *image);

#ifdef __cplusplus
}
#endif // __cplusplus
