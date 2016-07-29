#ifndef H3076EA06_5CF2_461B_BAC0_131AA1B74A0C
#define H3076EA06_5CF2_461B_BAC0_131AA1B74A0C

#include <tlp/base/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, template<typename T> class Func> struct Map;

template<template<typename T> class Func>
struct Map<NullType, Func>
{
    using Result = NullType;
};

template<typename Head, typename Tail, template<typename T> class Func>
struct Map<TypeElem<Head, Tail>, Func>
{
    using Result = TypeElem<typename Func<Head>::Result, typename Map<Tail, Func>::Result>;
};

TLP_NS_END

#define __map(...) typename TLP_NS::Map<__VA_ARGS__>::Result

#endif
