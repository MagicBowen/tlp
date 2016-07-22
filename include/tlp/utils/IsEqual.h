#ifndef HD78971D5_93C8_49CC_829C_C4FC7A9FB860
#define HD78971D5_93C8_49CC_829C_C4FC7A9FB860

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct IsEqual
{
    enum{ Value = false };
};

template<typename T>
struct IsEqual<T, T>
{
    enum{ Value = true };
};

TLP_NS_END

#define IS_EQUAL(...) TLP_NS::IsEqual<__VA_ARGS__>::Value

#endif
