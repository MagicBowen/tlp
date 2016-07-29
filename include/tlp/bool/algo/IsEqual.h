#ifndef HD78971D5_93C8_49CC_829C_C4FC7A9FB860
#define HD78971D5_93C8_49CC_829C_C4FC7A9FB860

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct IsEqual
{
    using Result = FalseType;
};

template<typename T>
struct IsEqual<T, T>
{
    using Result = TrueType;
};

TLP_NS_END

#define __is_eq(...)   typename TLP_NS::IsEqual<__VA_ARGS__>::Result

#endif
