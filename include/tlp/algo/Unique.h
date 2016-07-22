#ifndef H84135D9D_79ED_463A_B00F_3F69AF566176
#define H84135D9D_79ED_463A_B00F_3F69AF566176

#include <tlp/algo/Erase.h>

TLP_NS_BEGIN

template<typename TL> struct Unique;

template<>
struct Unique<NullType>
{
    using Result = NullType;
};

template<typename H, typename T>
struct Unique<TypeElem<H, T>>
{
    using Result = TypeElem<H, typename Erase<typename Unique<T>::Result, H>::Result>;
};

TLP_NS_END

#define UNIQUE(...) typename TLP_NS::Unique<__VA_ARGS__>::Result

#endif
