#ifndef H5A3A89FE_8544_461C_910C_7769C830E9C1
#define H5A3A89FE_8544_461C_910C_7769C830E9C1

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T> struct Dec;

template<int V>
struct Dec<IntType<V>>
{
    using Result = IntType<V - 1>;
};

TLP_NS_END

#define __dec(...)    typename TLP_NS::Dec<__VA_ARGS__>::Result

#endif
