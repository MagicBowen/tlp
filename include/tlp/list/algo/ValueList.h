#ifndef HF02C640B_085C_44AC_81E3_8CAE73350980
#define HF02C640B_085C_44AC_81E3_8CAE73350980

#include <tlp/list/TypeElem.h>
#include <tlp/base/NullType.h>
#include <tlp/int/IntType.h>

TLP_NS_BEGIN

template<int Head, int ...Tails>
struct ValueList
{
    using Result = TypeElem<IntType<Head>, typename ValueList<Tails...>::Result>;
};

template<int H>
struct ValueList<H>
{
    using Result = TypeElem<IntType<H>, NullType>;
};

TLP_NS_END

#define __value_list(...) typename TLP_NS::ValueList<__VA_ARGS__>::Result

#endif
