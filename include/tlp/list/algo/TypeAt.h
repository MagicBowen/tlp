#ifndef H3E904CF8_07E3_4046_983D_13484B3DB98B
#define H3E904CF8_07E3_4046_983D_13484B3DB98B

#include <tlp/list/TypeElem.h>
#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename TL, typename Index> struct TypeAt;

template<int V>
struct TypeAt<NullType, IntType<V>>
{
    using Result = NullType;
};

template<typename H, typename T>
struct TypeAt<TypeElem<H, T>, IntType<0>>
{
    using Result = H;
};

template<typename H, typename T, int i>
struct TypeAt<TypeElem<H, T>, IntType<i>>
{
    static_assert(i > 0, "Index is not in the valid range!");

    using Result = typename TypeAt<T , IntType<i - 1>>::Result;
};

TLP_NS_END

#define __at(...) typename TLP_NS::TypeAt<__VA_ARGS__>::Result

#endif
