#ifndef H4E05AF83_73C7_4843_9C95_D7ACC20D2ED6
#define H4E05AF83_73C7_4843_9C95_D7ACC20D2ED6

#include <tlp/base/NullType.h>
#include <tlp/list/TypeElem.h>
#include <tlp/bool/algo/Select.h>

TLP_NS_BEGIN

template<typename TL, template<typename T> class Pred> struct Filter;

template<template<typename T> class Pred>
struct Filter<NullType, Pred>
{
    using Result = NullType;
};

template<typename Head, typename Tail, template<typename T> class Pred>
struct Filter<TypeElem<Head, Tail>, Pred>
{
    using Result = typename Select< typename Pred<Head>::Result,
                                    TypeElem<Head, typename Filter<Tail, Pred>::Result>,
                                    typename Filter<Tail,Pred>::Result>::Result;
};

TLP_NS_END

#define __filter(...) typename TLP_NS::Filter<__VA_ARGS__>::Result

#endif
