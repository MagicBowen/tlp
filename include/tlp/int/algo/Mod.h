#ifndef H7182635A_9E73_4A84_84AA_5C4B94ECB2C9
#define H7182635A_9E73_4A84_84AA_5C4B94ECB2C9

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Mod;

template<int V1, int V2>
struct Mod<IntType<V1>, IntType<V2>>
{
    static_assert(V2 != 0, "Zero should not be used in modulus operation!");

    using Result = IntType<V1 % V2>;
};

TLP_NS_END

#define __mod(...)    typename TLP_NS::Mod<__VA_ARGS__>::Result
#endif
