//
// Created by zhaojunhe on 2018/11/14.
//
#pragma once

// 类型的运算

#include <type_traits>

namespace mbgl {

template<typename ...Ts>
struct TypeList {
    template<template<class...> class T, class... Ps>
    using ExpandInto = T<Ts..., Ps...>;
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

template<typename...>
struct TypeListConcat;

template<>
struct TypeListConcat<> {
    using Type = TypeList<>;
};

template<typename... As>
struct TypeListConcat<TypeList<As...>> {
    using Type = TypeList<As...>;
};

template<typename... As, typename... Bs, typename... Rs>
struct TypeListConcat<TypeList<As...>, TypeList<Bs...>, Rs...> {
    using Type = typename TypeListConcat<TypeList<As..., Bs...>, Rs...>::Type;
};

} // namespace detail

template<typename TypeList, template<typename> class Predicate>
using FilteredTypeList = typename detail::TypeFilter<TypeList, Predicate>::Type;

template<typename... Ts>
using TypeListConcat = typename detail::TypeListConcat<Ts...>::Type;
} // namespace mbgl
