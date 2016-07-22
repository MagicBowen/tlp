#ifndef H4C7D264B_067B_4419_86B3_50BBEB53FC0B
#define H4C7D264B_067B_4419_86B3_50BBEB53FC0B

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<bool condition, typename T, typename U>
struct IfThenElse
{
    using Result = T;
};

template<typename T, typename U>
struct IfThenElse<false, T, U>
{
    using Result = U;
};

TLP_NS_END

#define IF_THEN_ELSE(...) typename TLP_NS::IfThenElse<__VA_ARGS__>::Result

#endif
