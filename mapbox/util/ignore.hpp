//
// Created by zhaojunhe on 2018/10/24.
//
#pragma once

#include <initializer_list>

namespace mbgl {
namespace util {

template<class T>
void ignore(std::initializer_list<T>) {}

inline void ignore(std::initializer_list<int>) {}

} // namespace util
} // namespace mbgl
