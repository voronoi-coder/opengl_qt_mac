//
// Created by zhaojunhe on 2018/11/12.
//
#pragma once

#include <cstdio>
#include <gl/object.hpp>
#include <gl/draw_mode.hpp>

namespace mbgl {
namespace gl {

template<class V, class DrawMode = Indexed>
class VertexBuffer {
public:
    using Vertex = V;
    static constexpr std::size_t vertexSize = sizeof(Vertex);

    std::size_t vertexCount;
    UniqueBuffer buffer;
};

} // namespace gl
} // namespace mbgl