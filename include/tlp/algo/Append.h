#ifndef HFC7E5996_A206_4CE7_8BE5_92E88E137F40
#define HFC7E5996_A206_4CE7_8BE5_92E88E137F40

#include <tlp/list/TypeList.h>

TLP_NS_BEGIN

template<typename TL, typename T> struct Append;

template<>
struct Append<NullType, NullType>
{
    using Result = NullType;
};

template<typename T>
struct Append<NullType, T>
{
    using Result = typename TypeList<T>::Result;
};

template<typename H, typename T>
struct Append<NullType, TypeElem<H, T>>
{
    using Result = TypeElem<H, T>;
};

template<typename Head, typename Tail, typename T>
struct Append<TypeElem<Head, Tail>, T>
{
    using Result = TypeElem<Head, typename Append<Tail, T>::Result>;
};

TLP_NS_END

#define __append(...) typename TLP_NS::Append<__VA_ARGS__>::Result

#endif
