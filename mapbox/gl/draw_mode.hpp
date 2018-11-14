//
// Created by zhaojunhe on 2018/11/14.
//

#pragma once

#include <gl/types.hpp>

namespace mbgl {
namespace gl {

// Special draw mode for use with VertexVector<Indexed, Vertex>, in which
// case the true draw mode is denoted by the IndexVector type.
class Indexed {
public:
    static constexpr std::size_t bufferGroupSize = 1;
};

} // namespace gl
} // namespace mbgl
