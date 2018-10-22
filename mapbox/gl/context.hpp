//
// Created by zhaojunhe on 2018/10/22.
//
#pragma once

#include <cstdint>
#include <util/nocopyable.hpp>

namespace mbgl {
namespace gl {

class Context : private util::nocopyable {
public:
    Context();

    ~Context();

public:
    const uint32_t maximumVertexBindingCount;
};

} // namespace gl
} // namespace mbgl
