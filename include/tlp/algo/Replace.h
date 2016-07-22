#ifndef H12A8EB65_32BB_4F29_9946_3A9D1DEACC80
#define H12A8EB65_32BB_4F29_9946_3A9D1DEACC80

#include <tlp/tlp.h>
#include <tlp/core/NullType.h>

TLP_NS_BEGIN

template<typename TL, typename T, typename U> struct Replace;

template<typename T, typename U>
struct Replace<NullType, T, U>
{
    using Result = NullType;
};

template<typename TL, typename T>
struct Replace<TL, T, T>
{
    using Result = TL;
};

template<typename Tail, typename T, typename U>
struct Replace<TypeElem<T, Tail>, T, U>
{
    using Result = TypeElem<U, Tail>;
};

template<typename Head, typename Tail, typename T, typename U>
struct Replace<TypeElem<Head, Tail>, T, U>
{
    using Result = TypeElem<Head, typename Replace<Tail, T, U>::Result>;
};

TLP_NS_END

#define REPLACE(...) typename TLP_NS::Replace<__VA_ARGS__>::Result

#endif
