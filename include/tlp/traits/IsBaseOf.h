#ifndef H57116D63_BF80_40BF_9D76_424F8AFD23DF
#define H57116D63_BF80_40BF_9D76_424F8AFD23DF

#include <tlp/traits/IsConvertible.h>
#include <tlp/bool/algo/IsEqual.h>
#include <tlp/bool/algo/Not.h>
#include <tlp/bool/algo/And.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct IsBaseOf
{
    using Result = typename And<typename IsConvertible<const U*, const T*>::Result,
                                typename And<typename Not<typename IsEqual<const T*, const void*>::Result>::Result,
                                             typename Not<typename IsEqual<const T, const U>::Result>::Result>::Result>::Result;
};

TLP_NS_END

#define __is_base_of(...)   typename TLP_NS::IsBaseOf<__VA_ARGS__>::Result

#endif
