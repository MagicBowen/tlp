#ifndef HF8EC3192_BE24_490A_A92A_636741798977
#define HF8EC3192_BE24_490A_A92A_636741798977

#include <tlp/base/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename Head, typename ...Tails>
struct TypeList
{
    using Result = TypeElem<Head, typename TypeList<Tails...>::Result>;
};

template<typename H>
struct TypeList<H>
{
    using Result = TypeElem<H, NullType>;
};

TLP_NS_END

#define __type_list(...) typename TLP_NS::TypeList<__VA_ARGS__>::Result

#endif
