#include <gl_functions.hpp>

#include <QOpenGLContext>
#include <QOpenGLFunctions>

namespace mbgl {
namespace platform {

void (* const glActiveTexture)(GLenum) = [](auto... args){
    return QOpenGLContext::currentContext()->functions()->glActiveTexture(args...);
};

void (* const glAttachShader)(GLuint, GLuint) = [](auto... args){
    return QOpenGLContext::currentContext()->functions()->glAttachShader(args...);
};

}  // namespace platform
}  // namespace mbgl
