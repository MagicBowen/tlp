#ifndef H3E904CF8_07E3_4046_983D_13484B3DB98B
#define H3E904CF8_07E3_4046_983D_13484B3DB98B

#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, unsigned int index> struct TypeAt;

template<typename H, typename T>
struct TypeAt<TypeElem<H, T>, 0>
{
    using Result = H;
};

template<typename H, typename T, unsigned int i>
struct TypeAt<TypeElem<H, T>, i>
{
    using Result = typename TypeAt<T , i - 1>::Result;
};

TLP_NS_END

#define __at(...) typename TLP_NS::TypeAt<__VA_ARGS__>::Result

#endif
