#ifndef H8C847725_6D6C_4BC3_876E_35E3B18420AC
#define H8C847725_6D6C_4BC3_876E_35E3B18420AC

#include <tlp/list/algo/TypeList.h>
#include <tlp/list/algo/TypeAt.h>
#include <tlp/list/EmptyList.h>

TLP_NS_BEGIN

template<typename T>
struct LambdaTraits
: LambdaTraits<decltype(&T::operator())>
{
};

template<typename C, typename R, typename ... Args>
struct LambdaTraits<R (C::*)(Args...) const>
{
    using ReturnType = R;
    using ParaTypes = typename TypeList<Args...>::Result;
};

TLP_NS_END

#define __lambda_return(...)  typename TLP_NS::LambdaTraits<__VA_ARGS__>::ReturnType
#define __lambda_paras(...)   typename TLP_NS::LambdaTraits<__VA_ARGS__>::ParaTypes
#define __lambda_para(lambda, index) __at(__lambda_paras(lambda), __int(index))

#endif
