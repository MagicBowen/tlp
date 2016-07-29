#ifndef HEA2541B0_450B_4318_B6E3_6D078A21EAB1
#define HEA2541B0_450B_4318_B6E3_6D078A21EAB1

#include <tlp/base/NullType.h>
#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename T>
struct Valid
{
    using Result = TrueType;
};

template<>
struct Valid<NullType>
{
    using Result = FalseType;
};

TLP_NS_END

#define __valid(...)    typename TLP_NS::Valid<__VA_ARGS__>::Result

#endif
