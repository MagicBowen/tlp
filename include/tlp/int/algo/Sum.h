#ifndef H74E3CA45_5B6D_4F7C_B218_E6959BAB2FA9
#define H74E3CA45_5B6D_4F7C_B218_E6959BAB2FA9

#include <tlp/int/algo/Add.h>

TLP_NS_BEGIN

template<typename ...Numbers> struct Sum;

template<typename Number, typename ...LeftNumbers>
struct Sum<Number, LeftNumbers...>
{
    using Result = typename Add<Number, typename Sum<LeftNumbers...>::Result>::Result;
};

template<> struct Sum<>
{
    using Result = IntType<0>;
};

TLP_NS_END

#define __sum(...)  typename TLP_NS::Sum<__VA_ARGS__>::Result

#endif
