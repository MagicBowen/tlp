#ifndef H3D22A656_83FD_4CBB_8612_320370919EB0
#define H3D22A656_83FD_4CBB_8612_320370919EB0

#include <tlp/list/TypeElem.h>
#include <tlp/base/NullType.h>

TLP_NS_BEGIN

template<typename TL1, typename TL2, template<typename T1, typename T2> class Func> struct Transform;

template<template<typename T1, typename T2> class Func>
struct Transform<NullType, NullType, Func>
{
    using Result = NullType;
};

template<typename TL, template<typename T1, typename T2> class Func>
struct Transform<NullType, TL, Func>
{
    using Result = TL;
};

template<typename TL, template<typename T1, typename T2> class Func>
struct Transform<TL, NullType, Func>
{
    using Result = TL;
};

template<typename Head1, typename Tail1,
         typename Head2, typename Tail2,
         template<typename T1, typename T2> class Func>
struct Transform<TypeElem<Head1, Tail1>, TypeElem<Head2, Tail2>, Func>
{
    using Result = TypeElem<typename Func<Head1, Head2>::Result, typename Transform<Tail1, Tail2, Func>::Result>;
};

TLP_NS_END

#define __transform(...)    typename TLP_NS::Transform<__VA_ARGS__>::Result

#endif
