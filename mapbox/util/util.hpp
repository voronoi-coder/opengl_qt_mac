//
// Created by zhaojunhe on 2018/12/10.
//
#pragma once

// GCC 4.9 compatibility
#if !defined(__GNUC__) || __GNUC__ >= 5
#define MBGL_CONSTEXPR constexpr
#else
#define MBGL_CONSTEXPR inline
#endif
