#ifndef HD43494FD_A0F6_4B05_8E55_E154B9F49A78
#define HD43494FD_A0F6_4B05_8E55_E154B9F49A78

#include <tlp/type/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, typename T> struct IndexOf;

template<typename T>
struct IndexOf<NullType, T>
{
    enum { Value = -1 };
};

template<typename Tail, typename T>
struct IndexOf<TypeElem<T, Tail>, T>
{
    enum { Value = 0 };
};

template<typename Head, typename Tail, typename T>
struct IndexOf<TypeElem<Head, Tail>, T>
{
private:
    enum { Temp = IndexOf<Tail, T>::Value };

public:
    enum { Value = (Temp == -1) ? -1 : 1 + Temp };
};

TLP_NS_END

#define __index_of(...) TLP_NS::IndexOf<__VA_ARGS__>::Value

#endif
