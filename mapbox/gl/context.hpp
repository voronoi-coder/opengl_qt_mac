//
// Created by zhaojunhe on 2018/10/22.
//
#pragma once

#include <util/nocopyable.hpp>
#include <gl/types.hpp>
#include <gl/gl_functions.hpp>
#include <gl/state.hpp>

#include <vector>

namespace mbgl {
namespace gl {

constexpr size_t TextureMax = 64;

class Context {

public:
     const uint32_t maximumVertexBindingCount = 16;

public:
    std::vector<TextureID> pooledTextures;

    std::vector<ProgramID> abandonedPrograms;
    std::vector<ShaderID> abandonedShaders;
    std::vector<BufferID> abandonedBuffers;
    std::vector<TextureID> abandonedTextures;
    std::vector<VertexArrayID> abandonedVertexArrays;
    std::vector<FramebufferID> abandonedFramebuffers;
    std::vector<RenderbufferID> abandonedRenderbuffers;
};

} // namespace gl
} // namespace mbgl
