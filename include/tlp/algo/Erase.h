#ifndef H73C57738_42EF_4AAF_89A3_5AFC336EF6CB
#define H73C57738_42EF_4AAF_89A3_5AFC336EF6CB

#include <tlp/type/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, typename T> struct Erase;

template<typename T>
struct Erase<NullType, T>
{
    using Result = NullType;
};

template<typename H, typename T>
struct Erase<TypeElem<H, T>, H>
{
    using Result = T;
};

template<typename Head, typename Tail, typename T>
struct Erase<TypeElem<Head, Tail>, T>
{
    using Result = TypeElem<Head, typename Erase<Tail, T>::Result>;
};

TLP_NS_END

#define __erase(...) typename TLP_NS::Erase<__VA_ARGS__>::Result

#endif
