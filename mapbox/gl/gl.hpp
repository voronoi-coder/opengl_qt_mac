//
// Created by zhaojunhe on 2018/9/26.
//
#pragma once

#include <gl_impl.hpp>

namespace mbgl {
namespace gl {

struct Error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

void checkError(const char *cmd, const char *file, int line);

} // namespace gl
} // namespace mbgl