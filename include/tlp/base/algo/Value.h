#ifndef HB1BA0321_BE39_427C_BF4F_6DDA75A22650
#define HB1BA0321_BE39_427C_BF4F_6DDA75A22650

#include <tlp/tlp.h>
#include <tlp/base/NullType.h>
#include <tlp/base/EmptyType.h>

TLP_NS_BEGIN

template<typename T>
struct Value
{
    enum { Result = T::Value };
};

template<>
struct Value<NullType>
{
    enum { Result = 0xFFFFFFFF };
};

template<>
struct Value<EmptyType>
{
    enum { Result = 0 };
};

TLP_NS_END

#define __value(...)    TLP_NS::Value<__VA_ARGS__>::Result

#endif
