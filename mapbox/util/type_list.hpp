//
// Created by zhaojunhe on 2018/11/14.
//
#pragma once

#include <type_traits>

namespace mbgl {

template<typename ...>
class TypeList {
};

namespace detail {

template<typename, typename>
struct TypeCons;

template<typename T, typename ...Ts>
struct TypeCons<T, TypeList<Ts...>> {
    using Type = TypeList<T, Ts...>;
};

// the number of explicitly written template arguments can not differ from
// the number of template parameters in the primary template, but variadic templates and default template arguments.
template<typename, template<typename> class>
struct TypeFilter {
};

template<template<typename> class Predicate>
struct TypeFilter<TypeList<>, Predicate> {
    using Type = TypeList<>;
};

template<template<typename> class Predicate, typename T, typename ...Ts>
struct TypeFilter<TypeList<T, Ts...>, Predicate> {
public:
    using Tail = typename TypeFilter<TypeList<Ts...>, Predicate>::Type;
    using Type = std::conditional_t<Predicate<T>::value, TypeCons<T, Tail>, Tail>;
};
} // namespace detail

template<typename TypeList, template<typename> class Predicate>
using FilteredTypeList = typename detail::TypeFilter<TypeList, Predicate>::Type;
} // namespace mbgl
