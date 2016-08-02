#ifndef H3FBE49A9_543F_4C2D_B4BD_8DC554BAE313
#define H3FBE49A9_543F_4C2D_B4BD_8DC554BAE313

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Mul;

template<int V1, int V2>
struct Mul<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 * V2>;
};

TLP_NS_END

#define __mul(...)    typename TLP_NS::Mul<__VA_ARGS__>::Result

#endif
