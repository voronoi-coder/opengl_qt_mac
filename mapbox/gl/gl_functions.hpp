#pragma once

#include <cstddef>
// Pointers to OpenGL ES 2.0 functions. They must be
// initialized by the platform at linking time.


// 3 category: data, program, state, result

#ifndef NDEBUG
#define MBGL_CHECK_ERROR(cmd) ([&]() { struct __MBGL_CHECK_ERROR { ~__MBGL_CHECK_ERROR() noexcept(false) { mbgl::platform::glCheckError(#cmd, __FILE__, __LINE__); } } __MBGL_CHECK_ERROR; return cmd; }())
#else
#define MBGL_CHECK_ERROR(cmd) (cmd)
#endif


namespace mbgl {
namespace platform {

using GLbitfield = unsigned int;
using GLboolean = unsigned char;
using GLchar = char;
using GLdouble = double;
using GLenum = unsigned int;
using GLfloat = float;
using GLint = int;
using GLsizei = int;
using GLubyte = unsigned char;
using GLuint = unsigned int;
using GLvoid = void;

#if defined(_WIN32)
using GLintptr = long long;
using GLsizeiptr = long long;
#else
using GLintptr = long;
using GLsizeiptr = long;
#endif


extern void (* const glActiveTexture)(GLenum);
extern void (* const glAttachShader)(GLuint, GLuint);
extern void (* const glBindAttribLocation)(GLuint, GLuint, const GLchar *);
extern void (* const glBindBuffer)(GLenum, GLuint);
extern void (* const glBindFramebuffer)(GLenum, GLuint);
extern void (* const glBindRenderbuffer)(GLenum, GLuint);
extern void (* const glBindTexture)(GLenum, GLuint);
extern void (* const glBlendColor)(GLfloat, GLfloat, GLfloat, GLfloat);
extern void (* const glBlendEquation)(GLenum);
extern void (* const glBlendEquationSeparate)(GLenum, GLenum);
extern void (* const glBlendFunc)(GLenum, GLenum);
extern void (* const glBlendFuncSeparate)(GLenum, GLenum, GLenum, GLenum);
extern void (* const glBufferData)(GLenum, GLsizeiptr, const void *, GLenum);
extern void (* const glBufferSubData)(GLenum, GLintptr, GLsizeiptr, const void *);
extern GLenum (* const glCheckFramebufferStatus)(GLenum);
extern void (* const glClear)(GLbitfield);
extern void (* const glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
extern void (* const glClearDepthf)(GLfloat);
extern void (* const glClearStencil)(GLint);
extern void (* const glColorMask)(GLboolean, GLboolean, GLboolean, GLboolean);
extern void (* const glCompileShader)(GLuint);
extern void (* const glCompressedTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
extern void (* const glCompressedTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
extern void (* const glCopyTexImage2D)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
extern void (* const glCopyTexSubImage2D)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
extern GLuint (* const glCreateProgram)();
extern GLuint (* const glCreateShader)(GLenum);
extern GLuint (* const glCullFace)(GLenum);
extern void (* const glDeleteBuffers)(GLsizei, const GLuint *);
extern void (* const glDeleteFrameBuffers)(GLsizei, const GLuint *);
extern void (* const glDeleteProgram)(GLuint);
extern void (* const glDeleteRenderBuffers)(GLsizei, const GLuint *);
extern void (* const glDeleteShaders)(GLuint);
extern void (* const glDeleteTextures)(GLsizei, const GLuint *);
extern void (* const glDepthFunc)(GLenum);
extern void (* const glDepthMask)(GLboolean);
extern void (* const glDepthRangef)(GLfloat, GLfloat);
extern void (* const glDetachShader)(GLuint, GLuint);
extern void (* const glDisable)(GLenum);
extern void (* const glDisableVertexAttribArray)(GLuint);
extern void (* const glDrawArrays)(GLenum mode, GLint, GLsizei);
extern void (* const glDrawElements)(GLenum mode, GLsizei, GLenum, const void *);
extern void (* const glEnable)(GLenum);
extern void (* const glEnableVertexAttribArray)(GLuint);
extern void (* const glFinish)();
extern void (* const glFlush)();
extern void (* const glFramebufferRenderbuffer)(GLenum, GLenum, GLenum, GLuint);
extern void (* const glFramebufferTexture2D)(GLenum, GLenum, GLenum, GLuint, GLint);
extern void (* const glFrontFace)(GLenum);
extern void (* const glGenBuffers)(GLsizei, GLuint *);
extern void (* const glGenFramebuffers)(GLsizei, GLuint *);
extern void (* const glGenRenderbuffers)(GLsizei, GLuint *);
extern void (* const glGenTextures)(GLsizei, GLuint *);
extern void (* const glGenerateMipmap)(GLenum);
extern void (* const glGetBooleanv)(GLenum, GLboolean *);
extern void (* const glGetIntegerv)(GLenum, GLint *);
extern void (* const glGetFloatv)(GLenum, GLfloat *);
extern void (* const glGetActiveAttrib)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
extern void (* const glGetActiveUniform)(GLuint, GLuint, GLsizei, GLsizei, GLint *, GLenum *, GLchar *);
extern void (* const glGetAttachedShaders)(GLuint, GLsizei, GLsizei *, GLuint *);
extern void (* const glGetAttribLocation)(GLuint, GLchar *);
extern void (* const glGetBufferParameteriv)(GLenum, GLenum, GLint *);
extern GLenum (* glGetError)();
extern void (* const glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint *);
extern void (* const glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (* const glGetProgramiv)(GLuint, GLenum, GLint *);
extern void (* const glGetRenderbufferParameteriv)(GLenum, GLenum, GLint *);
extern void (* const glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (* const glGetShaderSource)(GLuint, GLsizei, GLsizei *, GLchar *);
extern void (* const glGetShaderiv)(GLuint, GLenum, GLint *);
extern const GLubyte *(*glGetString)(GLenum);
extern void (* const glGetTexParameterfv)(GLenum, GLenum, GLfloat *);
extern void (* const glGetTexParameteriv)(GLenum, GLenum, GLint *);
extern void (* const glGetUniformfv)(GLuint, GLint, GLfloat *);
extern void (* const glGetUniformiv)(GLuint, GLint, GLint *);
extern GLint (* const glGetUniformLocation)(GLuint, const GLchar *);
extern void (* const glGetVertexAttribfv)(GLuint, GLenum, GLfloat *);
extern void (* const glGetVertexAttribiv)(GLuint, GLenum, GLint *);
extern void (* const glGetVertexAttribPointerv)(GLuint, GLenum, void **);
extern void (* const glHint)(GLenum, GLenum);
extern GLboolean (* const glIsBuffer)(GLuint);
extern GLboolean (* const glIsEnabled)(GLenum);
extern GLboolean (* const glIsFramebuffer)(GLuint);
extern GLboolean (* const glIsProgram)(GLuint);
extern GLboolean (* const glIsRenderbuffer)(GLuint);
extern GLboolean (* const glIsShader)(GLuint);
extern GLboolean (* const glIsTexture)(GLuint);
extern void (* const glLineWidth)(GLfloat);
extern void (* const glLinkProgram)(GLuint program);
extern void (* const glPixelStorei)(GLenum, GLint);
extern void (* const glPolygonOffset)(GLfloat, GLfloat);
extern void (* const glReadPixels)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
extern void (* const glRenderbufferStorage)(GLenum, GLenum, GLsizei, GLsizei);
extern void (* const glSampleCoverage)(GLfloat, GLboolean);
extern void (* const glScissor)(GLint, GLint, GLsizei, GLsizei);
extern void (* const glShaderSource)(GLuint, GLsizei, const GLchar * const *, const GLint *);
extern void (* const glStencilFunc)(GLenum, GLint, GLuint);
extern void (* const glStencilFuncSeparate)(GLenum, GLenum, GLint, GLuint);
extern void (* const glStencilMask)(GLuint);
extern void (* const glStencilMaskSeparate)(GLenum, GLuint);
extern void (* const glStencilOp)(GLenum, GLenum, GLenum);
extern void (* const glStencilOpSeparate)(GLenum, GLenum, GLenum, GLenum);
extern void (* const glTexImage2D)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
extern void (* const glTexParameterf)(GLenum, GLenum, GLfloat);
extern void (* const glTexParameterfv)(GLenum, GLenum, const GLfloat *);
extern void (* const glTexParameteri)(GLenum, GLenum, GLint);
extern void (* const glTexParameteriv)(GLenum, GLenum, const GLint *);
extern void (* const glTexSubImage2D)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
extern void (* const glUniform1f)(GLint, GLfloat);
extern void (* const glUniform2f)(GLint, GLfloat, GLfloat);
extern void (* const glUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
extern void (* const glUniform4f)(GLint, GLfloat, GLfloat, GLfloat);
extern void (* const glUniform1i)(GLint, GLint);
extern void (* const glUniform2i)(GLint, GLint, GLint);
extern void (* const glUniform3i)(GLint, GLint, GLint, GLint);
extern void (* const glUniform4i)(GLint, GLint, GLint, GLint, GLint);
extern void (* const glUniform1fv)(GLint, GLsizei, const GLfloat *);
extern void (* const glUniform2fv)(GLint, GLsizei, const GLfloat *);
extern void (* const glUniform3fv)(GLint, GLsizei, const GLfloat *);
extern void (* const glUniform4fv)(GLint, GLsizei, const GLfloat *);
extern void (* const glUniform1iv)(GLint, GLsizei, const GLint *);
extern void (* const glUniform2iv)(GLint, GLsizei, const GLint *);
extern void (* const glUniform3iv)(GLint, GLsizei, const GLint *);
extern void (* const glUniform4iv)(GLint, GLsizei, const GLint *);
extern void (* const glUniformMatrix2fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (* const glUniformMatrix3fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (* const glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *);
extern void (* const glUseProgram)(GLuint);
extern void (* const glValidateProgram)(GLuint);
extern void (* const glVertexAttrib1f)(GLuint, GLfloat);
extern void (* const glVertexAttrib2f)(GLuint, GLfloat, GLfloat);
extern void (* const glVertexAttrib3f)(GLuint, GLfloat, GLfloat, GLfloat);
extern void (* const glVertexAttrib4f)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
extern void (* const glVertexAttrib1fv)(GLuint, const GLfloat *);
extern void (* const glVertexAttrib2fv)(GLuint, const GLfloat *);
extern void (* const glVertexAttrib3fv)(GLuint, const GLfloat *);
extern void (* const glVertexAttrib4fv)(GLuint, const GLfloat *);
extern void (* const glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
extern void (* const glViewport)(GLint, GLint, GLsizei, GLsizei);

#ifndef NDEBUG
void glCheckError(const char *cmd, const char *file, int line);
#endif

}  // namespace platform
}  // namespace mbgl
