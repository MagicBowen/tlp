#ifndef HAF187113_711A_4378_A5A9_BF5AF35484DA
#define HAF187113_711A_4378_A5A9_BF5AF35484DA

#include <tlp/algo/Fold.h>
#include <tlp/algo/Replace.h>

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
private:
    using Target = typename Fold<TypeElem<Head, Tail>, Head, Compare>::Result;
    using Temp = typename Replace<Tail, Target, Head>::Result;

public:
    using Result = TypeElem<Target, typename Sort<Temp, Compare>::Result>;
};

TLP_NS_END

#define SORT(...) typename TLP_NS::Sort<__VA_ARGS__>::Result

#endif
