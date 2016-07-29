#ifndef H8A29A5DB_3E7A_4A1F_AFFA_F07D59B2690A
#define H8A29A5DB_3E7A_4A1F_AFFA_F07D59B2690A

#include <tlp/base/NullType.h>
#include <tlp/list/TypeElem.h>
#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename TL, template<typename T> class Pred> struct Any;

template<template<typename T> class Pred>
struct Any<NullType, Pred>
{
    using Result = FalseType;
};

template<typename Head, typename Tail, template<typename T> class Pred>
struct Any<TypeElem<Head, Tail>, Pred>
{
    using Result = Select<Pred<Head>::Value, TrueType, Any<Tail, Pred>::Result>;
};

TLP_NS_END

#define __any(...)   typename TLP_NS<Any, __VA_ARGS__>::Result

#endif
