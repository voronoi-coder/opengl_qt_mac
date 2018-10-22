//
// Created by zhaojunhe on 2018/10/15.
//
#pragma once

#include <cstdint>

namespace mbgl {
namespace gl {

using BufferID = uint32_t;
using ProgramID = uint32_t;

enum class DataType : uint16_t {
    Byte = 0x1400,
    UnsignedByte = 0x1401,
    Short = 0x1402,
    UnsignedShort = 0x1403,
    Integer = 0x1404,
    UnsignedInteger = 0x1405,
    Float = 0x1406
};

// OpenGL does not formally define a type for attribute locations, but most APIs use
// GLuint. The exception is glGetAttribLocation, which returns GLint so that -1 can
// be used as an error indicator.
using AttributeLocation = uint32_t;

// OpenGL does not formally define a type for uniform locations, but all APIs use GLint.
// The value -1 is special, typically used as a placeholder for an unused uniform and
// "silently ignored".
using UniformLocation = int32_t;

} // namespace gl
} // namespace mbgl