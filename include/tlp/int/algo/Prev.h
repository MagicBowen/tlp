#ifndef H5A3A89FE_8544_461C_910C_7769C830E9C1
#define H5A3A89FE_8544_461C_910C_7769C830E9C1

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T> struct Prev;

template<int V>
struct Prev<IntType<V>>
{
    using Result = IntType<V - 1>;
};

TLP_NS_END

#define __prev(...)    typename TLP_NS::Prev<__VA_ARGS__>::Result

#endif
