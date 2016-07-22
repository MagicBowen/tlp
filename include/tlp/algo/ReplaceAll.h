#ifndef HC8B980BB_E8E6_4F63_BF1D_C44109D26E32
#define HC8B980BB_E8E6_4F63_BF1D_C44109D26E32

#include <tlp/algo/Replace.h>

TLP_NS_BEGIN

template<typename TL, typename T, typename U> struct ReplaceAll;

template<typename T, typename U>
struct ReplaceAll<NullType, T, U>
{
    using Result = NullType;
};

template<typename TL, typename T>
struct ReplaceAll<TL, T, T>
{
    using Result = TL;
};

template<typename Tail, typename T, typename U>
struct ReplaceAll<TypeElem<T, Tail>, T, U>
{
    using Result = TypeElem<U, typename Replace<Tail, T, U>::Result>;
};

template<typename Head, typename Tail, typename T, typename U>
struct ReplaceAll<TypeElem<Head, Tail>, T, U>
{
    using Result = TypeElem<Head, typename ReplaceAll<Tail, T, U>::Result>;
};

TLP_NS_END

#define REPLACE_ALL(...) typename TLP_NS::ReplaceAll<__VA_ARGS__>::Result

#endif
