#ifndef H57116D63_BF80_40BF_9D76_424F8AFD23DF
#define H57116D63_BF80_40BF_9D76_424F8AFD23DF

#include <tlp/utils/Convertible.h>
#include <tlp/utils/IsEqual.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct InheritsFrom
{
    enum { Value = Convertible<const U*, const T*>::Value &&
                  !IsEqual<const T*, const void*>::Value &&
                  !IsEqual<const T, const U>::Value };
};

TLP_NS_END

#define INHERITS_FROM(...) TLP_NS::InheritsFrom<__VA_ARGS__>::Value

#endif
