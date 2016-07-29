#ifndef H9443FEC6_D04B_4E94_8465_1420865C94CF
#define H9443FEC6_D04B_4E94_8465_1420865C94CF

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Or;

template<bool V1, bool V2>
struct Or<BoolType<V1>, BoolType<V2>>
{
    using Result = BoolType<V1 || V2>;
};

TLP_NS_END

#define __or(...)    typename TLP_NS::Or<__VA_ARGS__>::Result

#endif
