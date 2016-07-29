#ifndef H4C7D264B_067B_4419_86B3_50BBEB53FC0B
#define H4C7D264B_067B_4419_86B3_50BBEB53FC0B

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename Condition, typename T, typename U> struct Select;

template<typename T, typename U>
struct Select<TrueType, T, U>
{
    using Result = T;
};

template<typename T, typename U>
struct Select<FalseType, T, U>
{
    using Result = U;
};

TLP_NS_END

#define __select(...) typename TLP_NS::Select<__VA_ARGS__>::Result

#endif
