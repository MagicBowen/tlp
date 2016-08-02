#ifndef H75BC6D2C_12BE_4E89_931C_F533F19F4784
#define H75BC6D2C_12BE_4E89_931C_F533F19F4784

#include <tlp/list/TypeElem.h>
#include <tlp/base/NullType.h>
#include <tlp/int/IntType.h>
#include <tlp/int/algo/Add.h>

TLP_NS_BEGIN

template<typename TL> struct Length;

template<typename Head, typename Tail>
struct Length<TypeElem<Head, Tail>>
{
    using Result = typename Add<IntType<1>, typename Length<Tail>::Result>::Result;
};

template<>
struct Length<NullType>
{
    using Result = IntType<0>;
};

TLP_NS_END

#define __length(...)   typename TLP_NS::Length<__VA_ARGS__>::Result

#endif
