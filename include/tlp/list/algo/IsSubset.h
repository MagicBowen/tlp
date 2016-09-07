#ifndef HA5693FA4_43E3_4AC7_8300_59B950576EC7
#define HA5693FA4_43E3_4AC7_8300_59B950576EC7

#include <tlp/base/NullType.h>
#include <tlp/bool/BoolType.h>
#include <tlp/bool/algo/And.h>
#include <tlp/list/TypeElem.h>
#include <tlp/list/algo/IsIncluded.h>

TLP_NS_BEGIN

template<typename TL1, typename TL2> struct IsSubset;

template<typename TL>
struct IsSubset<NullType, TL>
{
    using Result = TrueType;
};

template<typename Head, typename Tail, typename TL>
struct IsSubset<TypeElem<Head, Tail>, TL>
{
    using Result = typename And<typename IsIncluded<TL, Head>::Result, typename IsSubset<Tail, TL>::Result>::Result;
};

TLP_NS_END

#define __is_subset(...)  typename TLP_NS::IsSubset<__VA_ARGS__>::Result

#endif
