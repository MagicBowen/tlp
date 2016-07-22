#ifndef HAF187113_711A_4378_A5A9_BF5AF35484DA
#define HAF187113_711A_4378_A5A9_BF5AF35484DA

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<typename TL, template<typename T1, typename T2> class Compare> struct Sort;

template<template<typename T1, typename T2> class Compare>
struct Sort<NullType, Compare>
{
    using Result = NullType;
};

template<typename Head, typename Tail, template<typename T1, typename T2> class Compare>
struct Sort<TypeElem<Head, Tail>, Compare>
{
//    using Result = typename
};

TLP_NS_END

#endif
