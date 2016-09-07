#ifndef HDBB1354D_2A0D_4455_9DF2_651BCF48EF45
#define HDBB1354D_2A0D_4455_9DF2_651BCF48EF45

#include <tlp/list/algo/IndexOf.h>

TLP_NS_BEGIN

template<typename TL, typename T>
struct IsIncluded
{
    using Result = typename Valid<typename IndexOf<TL, T>::Result>::Result;
};

TLP_NS_END

#define __is_included(...)  typename TLP_NS::IsIncluded<__VA_ARGS__>::Result

#endif
