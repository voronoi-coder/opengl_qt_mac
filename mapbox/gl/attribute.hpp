//
// Created by zhaojunhe on 2018/10/15.
//
#pragma once

#include <types.hpp>
#include <tuple>

#include <util/optional.hpp>
#include <util/type_list.hpp>
#include <set>

#include <gl/vertex_buffer.hpp>


namespace mbgl {
namespace gl {

template<class>
struct DataTypeOf;

template<>
struct DataTypeOf<int8_t> : std::integral_constant<DataType, DataType::Byte> {
};

class AttributeBinding {
public:
    DataType attributeType;
    uint8_t attributeSize;
    uint32_t attributeOffset;

    BufferID vertexBuffer;
    uint32_t vertexSize;
    uint32_t vertexOffset;

    friend bool operator==(const AttributeBinding &lhs, const AttributeBinding &rhs) {
        return std::tie(lhs.attributeType, lhs.attributeSize, lhs.attributeOffset, lhs.vertexBuffer, lhs.vertexSize,
                        lhs.vertexOffset)
               == std::tie(rhs.attributeType, rhs.attributeSize, rhs.attributeOffset, rhs.vertexBuffer, rhs.vertexSize,
                           rhs.vertexOffset);
    }
};

using AttributeBindingArray = std::vector<optional<AttributeBinding>>;

/*
    gl::Attribute<T,N> manages the binding of a vertex buffer to a GL program attribute.
      - T is the underlying primitive type (exposed as Attribute<T,N>::ValueType)
      - N is the number of components in the attribute declared in the shader (exposed as Attribute<T,N>::Dimensions)
*/

template<typename T, std::size_t N>
class Attribute {
public:
    using ValueType = T;
    static constexpr size_t Dimensions = N;
    using Value = std::array<T, N>;

    using Location = AttributeLocation;
    using Binding = AttributeBinding;

    /*
    Create a binding for this attribute.  The `attributeSize` parameter may be used to
    override the number of components available in the buffer for each vertex.  Thus,
    a buffer with only one float for each vertex can be bound to a `vec2` attribute
    */
    template<class Vertex, class DrawMode>
    static Binding
    binding(VertexBuffer<Vertex, DrawMode> &buffer, std::size_t attributeIndex, std::size_t attributeSize = N) {
        static_assert(std::is_standard_layout<Vertex>::value, "vertex type must use standard layout");
        assert(attributeSize >= 1);
        assert(attributeSize <= 4);
        assert(Vertex::attributeOffsets[attributeIndex] <= std::numeric_limits<uint32_t>::max());
        static_assert(sizeof(Vertex) <= std::numeric_limits<uint32_t>::max(), "vertex too large");

        return AttributeBinding{
                DataTypeOf<T>::value,
                attributeSize,
                static_cast<uint32_t>(Vertex::attributeOffsets[attributeIndex]),
                buffer.buffer,
                static_cast<uint32_t>(sizeof(Vertex)),
                0
        };
    }

    static optional<Binding> offsetBinding(const optional<Binding> &binding, std::size_t vertexOffset) {
        assert(vertexOffset <= std::numeric_limits<uint32_t>::max());
        if (binding) {
            AttributeBinding result = *binding;
            result.vertexOffset = static_cast<uint32_t>(vertexOffset);
            return result;
        } else {
            return binding;
        }
    }
};

#define MBGL_DEFINE_ATTRIBUTE(type_, n_, name_)         \
    struct name_{                                       \
        static auto name(){ return #name_;}             \
        using Type = ::mbgl::gl::Attribute<type_, n_>;  \
    };                                                  \


class Context;

void bindAttributeLocation(Context &, ProgramID, AttributeLocation, const char *);

std::set<std::string> getActiveAttributes(ProgramID);

template<typename... As>
class Attributes {
};

} // namespace gl
} // namespace mbgl






















