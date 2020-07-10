//
// Created by zhaojunhe on 2018/12/11.
//
#pragma once

#include <cmath>
#include <experimental/optional>
#include <string>

namespace CSSColorParser {

template<typename T>
using optional = std::experimental::optional<T>;

struct Color {
    inline Color() {}

    inline Color(unsigned char r_, unsigned char g_, unsigned char b_, float a_)
            : r(r_), g(g_), b(b_), a(a_ > 1 ? 1 : a_ < 0 ? 0 : a_) {
    }

    unsigned char r = 0, g = 0, b = 0;
    float a = 1.0f;
};

inline bool operator==(const Color &lhs, const Color &rhs) {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && ::fabs(lhs.a - rhs.a) < 0.0001f;
}

inline bool operator!=(const Color &lhs, const Color &rhs) {
    return !(lhs == rhs);
}

optional<Color> parse(const std::string &css_str);

} // namespace CSSColorParser
