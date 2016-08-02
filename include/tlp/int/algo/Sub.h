#ifndef H5363CEF5_E51E_4FBB_AF00_DEB9C0A1981E
#define H5363CEF5_E51E_4FBB_AF00_DEB9C0A1981E

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Sub;

template<int V1, int V2>
struct Sub<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 - V2>;
};

TLP_NS_END

#define __sub(...)    typename TLP_NS::Sub<__VA_ARGS__>::Result

#endif
