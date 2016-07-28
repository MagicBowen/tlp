#ifndef HB59984C7_38BC_4B83_BA98_213845BFFF81
#define HB59984C7_38BC_4B83_BA98_213845BFFF81

#include <tlp/type/EmptyType.h>
#include <tlp/type/NullType.h>
#include <tlp/list/TypeElem.h>

TLP_NS_BEGIN

template<typename TL,
         template<typename Atom, typename Base> class Unit,
         typename Root = EmptyType>
struct LinearInherits;

template<typename T,
         template<typename Atom, typename Base> class Unit,
         typename Root>
struct LinearInherits<TypeElem<T, NullType>, Unit, Root>
: Unit<T, Root>
{
};

template<typename Head,
         typename Tail,
         template<typename Atom, typename Base> class Unit,
         typename Root>
struct LinearInherits<TypeElem<Head, Tail>, Unit, Root>
: Unit<Head, LinearInherits<Tail, Unit, Root>>
{
};

TLP_NS_END

#define __linear_inherits(...) TLP_NS::LinearInherits<__VA_ARGS__>

#endif
