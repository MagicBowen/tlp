#ifndef H1EE79EA6_CA7E_4D39_A62E_4B4E5B2FBC2B
#define H1EE79EA6_CA7E_4D39_A62E_4B4E5B2FBC2B

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct And;

template<bool V1, bool V2>
struct And<BoolType<V1>, BoolType<V2>>
{
    using Result = BoolType<V1 && V2>;
};

TLP_NS_END

#define __and(...)    typename TLP_NS::And<__VA_ARGS__>::Result

#endif
