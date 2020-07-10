#include <gl_functions.hpp>

#include <stdio.h>

namespace mbgl {
namespace platform {

#ifndef NDEBUG
void glCheckError(const char *cmd, const char *file, int line) {

    if(GLenum err = glGetError()){
        printf("OpenGL Error %d: %s - %s:%d\n", err, cmd, file, line);
    }
}
#endif

} // namespace platform
} // namespace mbgl
