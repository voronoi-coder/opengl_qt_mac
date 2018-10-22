//
// Created by zhaojunhe on 2018/10/15.
//
#pragma once

#include <cstdint>

namespace mbgl {
namespace gl {

using BufferID = uint32_t;

enum class DataType : uint16_t {
    Byte = 0x1400,
    UnsignedByte = 0x1401,
    Short = 0x1402,
    UnsignedShort = 0x1403,
    Integer = 0x1404,
    UnsignedInteger = 0x1405,
    Float = 0x1406
};

} // namespace gl
} // namespace mbgl