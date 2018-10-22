//
// Created by zhaojunhe on 2018/10/15.
//
#pragma once

#include <types.hpp>
#include <tuple>

#include <util/optional.hpp>

namespace mbgl {
namespace gl {

class AttributeBinding {
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

} // namespace gl
} // namespace mbgl

