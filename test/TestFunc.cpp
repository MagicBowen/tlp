#include <tlp/test/Test.h>
#include <tlp/func/Forward.h>
#include <tlp/int/IntType.h>

FIXTURE(TestFunc)
{
    template<template<typename ...Paras> class F>
    struct Trans
    {
        template<typename ...Args>
        struct Func
        {
            using Result = typename F<Args...>::Result;
        };
    };

    template<template<typename T> class F>
    struct FuncInt
    {
        using Result = typename F<int>::Result;
    };

    TEST("should forward the paras to inner func args")
    {
        __func_forward_1(Func1, __int(sizeof(_1)));
//
//        ASSERT_EQ(FuncInt<Trans<Func1>::template Func>::Result, __int(8));
    };
};
