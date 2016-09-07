#ifndef H169A9C7C_32DE_4510_8829_D863224588C9
#define H169A9C7C_32DE_4510_8829_D863224588C9

#include <tlp/bool/BoolType.h>

TLP_NS_BEGIN

template<typename Cond, typename Func1, typename Func2>
struct SelectFunc
{
    using Result = typename Func2::Result;
};

template<typename Func1, typename Func2>
struct SelectFunc<TrueType, Func1, Func2>
{
    using Result = typename Func1::Result;
};

TLP_NS_END

#define __select_func(...) typename TLP_NS::SelectFunc<__VA_ARGS__>::Result

#endif
