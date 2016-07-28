#ifndef H75BC6D2C_12BE_4E89_931C_F533F19F4784
#define H75BC6D2C_12BE_4E89_931C_F533F19F4784

#include <tlp/type/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL> struct Length;

template<typename H, typename T>
struct Length<TypeElem<H, T>>
{
    enum{ Value = 1 + Length<T>::Value };
};

template<typename H>
struct Length<TypeElem<H, NullType>>
{
    enum{ Value = 1 };
};

TLP_NS_END

#define __length(...) TLP_NS::Length<__VA_ARGS__>::Value

#endif
