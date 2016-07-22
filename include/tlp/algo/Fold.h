#ifndef H243161B1_9A85_4DA5_AA89_99BBF804A352
#define H243161B1_9A85_4DA5_AA89_99BBF804A352

#include <tlp/base/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL, typename T, template<typename Acc, typename U> class Func> struct Fold;

template<typename T, template<typename Acc, typename U> class Func>
struct Fold<NullType, T, Func>
{
    using Result = T;
};

template<typename Head, typename Tail, typename T, template<typename Acc, typename U> class Func>
struct Fold<TypeElem<Head, Tail>, T, Func>
{
    using Result = typename Func<typename Fold<Tail, T, Func>::Result, Head>::Result;
};

TLP_NS_END

#define FOLD(...) typename TLP_NS::Fold<__VA_ARGS__>::Result

#endif
