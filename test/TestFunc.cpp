#include <tlp/test/Test.h>
#include <tlp/func/Forward.h>
#include <tlp/func/DefFunc.h>
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

    TEST("should forward the paras to inner func args")
    {
        __def_func_1(Func1, __int(sizeof(_1)));

        ASSERT_EQ(Trans<Func1>::template Func<long>::Result, __int(8));
    };
};
