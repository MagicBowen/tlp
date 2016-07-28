#ifndef H8A29A5DB_3E7A_4A1F_AFFA_F07D59B2690A
#define H8A29A5DB_3E7A_4A1F_AFFA_F07D59B2690A

#include <tlp/type/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, template<typename T> class Pred> struct Any;

template<template<typename T> class Pred>
struct Any<NullType, Pred>
{
    enum {Value = false};
};

template<typename Head, typename Tail, template<typename T> class Pred>
struct Any<TypeElem<Head, Tail>, Pred>
{
    enum {Value = Pred<Head>::Value ? true : Any<Tail, Pred>::Value};
};

TLP_NS_END

#define __any(...) TLP_NS::Any<__VA_ARGS__>::Value

#endif
