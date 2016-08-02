#ifndef H44BF8825_B3E4_40BE_B12D_74FE2EE883CB
#define H44BF8825_B3E4_40BE_B12D_74FE2EE883CB

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Add;

template<int V1, int V2>
struct Add<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 + V2>;
};

TLP_NS_END

#define __add(...)    typename TLP_NS::Add<__VA_ARGS__>::Result

#endif
