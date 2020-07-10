//
// Created by zhaojunhe on 2018/12/10.
//
#pragma once

#include <util/util.hpp>
#include <array>

namespace mbgl {
namespace util {

template<typename To, typename From, std::size_t Size,
        typename = std::enable_if_t<std::is_convertible<To, From>::value>>
MBGL_CONSTEXPR std::array<To, Size> convert(const std::array<From, Size> &from) {
    std::array<To, Size> to{{}};
    std::copy(std::begin(from), std::end(from), std::begin(to));
    return to;
}

} // namespace util
} // namespace mbgl