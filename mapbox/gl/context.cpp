//
// Created by zhaojunhe on 2018/10/22.
//

#include "context.hpp"
#include <gl.hpp>

namespace mbgl {
namespace gl {

Context::Context() : maximumVertexBindingCount([] {
    GLint value;
    MBGL_CHECK_ERROR(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value));
    return value;
}()) {}

} // namespace gl
} // namespace mbgl