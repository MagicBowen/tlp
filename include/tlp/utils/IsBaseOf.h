#ifndef H57116D63_BF80_40BF_9D76_424F8AFD23DF
#define H57116D63_BF80_40BF_9D76_424F8AFD23DF

#include <tlp/utils/IsConvertible.h>
#include <tlp/utils/IsEqual.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct IsBaseOf
{
    enum { Value = IsConvertible<const U*, const T*>::Value &&
                  !IsEqual<const T*, const void*>::Value &&
                  !IsEqual<const T, const U>::Value };
};

TLP_NS_END

#define IS_BASE_OF(...) TLP_NS::IsBaseOf<__VA_ARGS__>::Value

#endif
