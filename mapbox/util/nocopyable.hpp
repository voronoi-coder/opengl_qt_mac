//
// Created by zhaojunhe on 2018/10/22.
//
#pragma once

namespace mbgl {
namespace util {

class nocopyable {
public:
    nocopyable(const nocopyable &) = delete;

    void operator=(const nocopyable &) = delete;

protected:
    constexpr nocopyable() = default;

    ~nocopyable() = default;
};

} // namespace util
} // namespace mbgl