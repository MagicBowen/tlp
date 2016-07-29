#ifndef H37D127DF_B5A3_4DA6_A073_10FC6E8D7B45
#define H37D127DF_B5A3_4DA6_A073_10FC6E8D7B45

#include <tlp/bool/algo/Not.h>

TLP_NS_BEGIN

template<template<typename T> class Pred>
struct Negative
{
    template<typename U>
    struct Apply
    {
        using Result = typename Not<typename Pred<U>::Result>::Result;
    };
};

TLP_NS_END

#define __negative(...)  TLP_NS::Negative<__VA_ARGS__>::template Apply

#endif
