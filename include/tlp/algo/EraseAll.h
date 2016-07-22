#ifndef H786B59C9_447B_4575_AA49_431F969DC9B5
#define H786B59C9_447B_4575_AA49_431F969DC9B5

#include <tlp/core/NullType.h>
#include <tlp/core/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, typename T> struct EraseAll;

template<typename T>
struct EraseAll<NullType, T>
{
    using Result = NullType;
};

template<typename H, typename T>
struct EraseAll<TypeElem<H, T>, H>
{
    using Result = typename EraseAll<T, H>::Result;
};

template<typename Head, typename Tail, typename T>
struct EraseAll<TypeElem<Head, Tail>, T>
{
    using Result = TypeElem<Head, typename EraseAll<Tail, T>::Result>;
};

TLP_NS_END

#define ERASE_ALL(...) typename TLP_NS::EraseAll<__VA_ARGS__>::Result

#endif
