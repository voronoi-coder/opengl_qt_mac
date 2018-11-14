//
// Created by zhaojunhe on 2018/11/12.
//
#pragma once

#include <util/unique_resource.hpp>
#include <gl/types.hpp>


namespace mbgl {
namespace gl {

class Context;

namespace detail {

struct ProgramDeleter {
    Context *context;
    void operator()(ProgramID) const;
};
struct ShaderDeleter {
    Context *context;
    void operator()(ShaderID) const;
};
struct BufferDeleter {
    Context *context;
    void operator()(BufferID) const;
};
struct TextureDeleter {
    Context* context;
    void operator()(TextureID) const;
};
struct VertexArrayDeleter {
    Context* context;
    void operator()(VertexArrayID) const;
};
struct FramebufferDeleter {
    Context* context;
    void operator()(FramebufferID) const;
};
struct RenderbufferDeleter {
    Context* context;
    void operator()(RenderbufferID) const;
};


} // namespace detail


using UniqueProgram = std_experimental::unique_resource<ProgramID, detail::ProgramDeleter>;
using UniqueShader = std_experimental::unique_resource<ShaderID, detail::ShaderDeleter>;
using UniqueBuffer = std_experimental::unique_resource<BufferID, detail::ShaderDeleter>;
using UniqueTexture = std_experimental::unique_resource<TextureID, detail::ShaderDeleter>;
using UniqueVerterArray = std_experimental::unique_resource<VertexArrayID, detail::ShaderDeleter>;
using UniqueFramebuffer = std_experimental::unique_resource<FramebufferID, detail::ShaderDeleter>;
using UniqueRenderbuffer = std_experimental::unique_resource<RenderbufferID, detail::ShaderDeleter>;

} // namespace gl
} // namespace mbgl