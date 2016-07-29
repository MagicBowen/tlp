#ifndef HDD5F16F3_609B_4ADD_8AFD_D8841305227D
#define HDD5F16F3_609B_4ADD_8AFD_D8841305227D

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<int V>
struct IntType
{
    enum { Value = V };
};

TLP_NS_END

#define __int(value)    TLP_NS::IntType<value>

#endif
