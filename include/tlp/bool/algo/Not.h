#ifndef HA33791DD_3D55_4910_A817_CEDC0A9A8BCE
#define HA33791DD_3D55_4910_A817_CEDC0A9A8BCE

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename B> struct Not;

template<bool V>
struct Not<BoolType<V>>
{
    using Result = BoolType<!V>;
};

TLP_NS_END

#define __not(...)  typename TLP_NS::Not<__VA_ARGS__>::Result

#endif
