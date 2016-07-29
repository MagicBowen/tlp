#ifndef H502EEDE4_6A0E_4115_A52B_0C4FE4130202
#define H502EEDE4_6A0E_4115_A52B_0C4FE4130202

#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<typename T1, typename T2> struct Div;

template<int V1, int V2>
struct Div<IntType<V1>, IntType<V2>>
{
    static_assert(V2 != 0, "Zero should not be used in divide operation!");

    using Result = IntType<V1 / V2>;
};

TLP_NS_END

#define __div(...)    typename TLP_NS::Div<__VA_ARGS__>::Result

#endif
