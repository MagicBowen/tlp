#ifndef H4C7D264B_067B_4419_86B3_50BBEB53FC0B
#define H4C7D264B_067B_4419_86B3_50BBEB53FC0B

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename Condition, typename Then, typename Else> struct IfThenElse;

template<typename Then, typename Else>
struct IfThenElse<TrueType, Then, Else>
{
    using Result = Then;
};

template<typename Then, typename Else>
struct IfThenElse<FalseType, Then, Else>
{
    using Result = Else;
};

TLP_NS_END

#define __if(...) typename TLP_NS::IfThenElse<__VA_ARGS__>::Result

#endif
