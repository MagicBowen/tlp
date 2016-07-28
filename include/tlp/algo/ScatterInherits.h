#ifndef H03086BA7_F23F_457A_8381_F2D0060B3825
#define H03086BA7_F23F_457A_8381_F2D0060B3825

#include <tlp/list/TypeElem.h>
#include <tlp/type/NullType.h>

TLP_NS_BEGIN

template<typename TL, template<typename> class Unit> struct ScatterInherits;

template<template<typename> class Unit>
struct ScatterInherits<NullType, Unit>
{
};

template<typename Atom, template<typename> class Unit>
struct ScatterInherits : Unit<Atom>
{
};

template<typename Head, typename Tail, template<typename> class Unit>
struct ScatterInherits<TypeElem<Head, Tail>, Unit>
: ScatterInherits<Head, Unit>
, ScatterInherits<Tail, Unit>
{
};

TLP_NS_END

#define __scatter_inherits(...) TLP_NS::ScatterInherits<__VA_ARGS__>

#endif
