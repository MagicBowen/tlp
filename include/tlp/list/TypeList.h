#ifndef HF8EC3192_BE24_490A_A92A_636741798977
#define HF8EC3192_BE24_490A_A92A_636741798977

#include <tlp/type/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename H, typename ...TAILS>
struct TypeList
{
    using Result = TypeElem<H, typename TypeList<TAILS...>::Result>;
};

template<typename H>
struct TypeList<H>
{
    using Result = TypeElem<H, NullType>;
};

TLP_NS_END

#define __type_list(...) typename TLP_NS::TypeList<__VA_ARGS__>::Result

#endif
