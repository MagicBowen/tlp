#ifndef HD43494FD_A0F6_4B05_8E55_E154B9F49A78
#define HD43494FD_A0F6_4B05_8E55_E154B9F49A78

#include <tlp/list/TypeElem.h>
#include <tlp/base/algo/Valid.h>
#include <tlp/base/algo/Value.h>
#include <tlp/int/IntType.h>
#include <tlp/bool/algo/IfThenElse.h>

TLP_NS_BEGIN

template<typename TL, typename T> struct IndexOf;

template<typename T>
struct IndexOf<NullType, T>
{
    using Result = NullType;
};

template<typename Tail, typename T>
struct IndexOf<TypeElem<T, Tail>, T>
{
    using Result = IntType<0>;
};

template<typename Head, typename Tail, typename T>
struct IndexOf<TypeElem<Head, Tail>, T>
{
private:
    using Temp = typename IndexOf<Tail, T>::Result;

public:
    using Result = typename IfThenElse<typename Valid<Temp>::Result, IntType<Value<Temp>::Result + 1>, NullType>::Result;
};

TLP_NS_END

#define __index_of(...)    typename TLP_NS::IndexOf<__VA_ARGS__>::Result

#endif
