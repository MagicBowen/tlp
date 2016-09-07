#ifndef H21D575F7_0565_4E05_A4D9_27DEB84367C7
#define H21D575F7_0565_4E05_A4D9_27DEB84367C7

#include <tlp/base/NullType.h>
#include <tlp/bool/BoolType.h>
#include <tlp/bool/algo/Or.h>
#include <tlp/list/TypeElem.h>
#include <tlp/list/algo/IsSubset.h>

TLP_NS_BEGIN

template<typename TL, typename TLS> struct Belong;

template<typename TL>
struct Belong<TL, NullType>
{
    using Result = FalseType;
};

template<typename TL, typename Head, typename Tail>
struct Belong<TL, TypeElem<Head, Tail>>
{
    using Result = typename Or< typename IsSubset<TL, Head>::Result
                              , typename Belong<TL, Tail>::Result>::Result;
};

TLP_NS_END

#define __belong(...)  typename TLP_NS::Belong<__VA_ARGS__>::Result

#endif
