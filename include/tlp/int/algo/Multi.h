#ifndef H3FBE49A9_543F_4C2D_B4BD_8DC554BAE313
#define H3FBE49A9_543F_4C2D_B4BD_8DC554BAE313

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Multi;

template<int V1, int V2>
struct Multi<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 * V2>;
};

TLP_NS_END

#define __multi(...)    typename TLP_NS::Multi<__VA_ARGS__>::Result

#endif
