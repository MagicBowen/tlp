#ifndef H1E74E698_2981_445A_B4F0_CCCC4FDB50CD
#define H1E74E698_2981_445A_B4F0_CCCC4FDB50CD

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<typename H, typename T>
struct TypeElem
{
    using Head = H;
    using Tail = T;
};

TLP_NS_END

#define __type_elem(...)    TLP_NS::TypeElem<__VA_ARGS__>

#endif
