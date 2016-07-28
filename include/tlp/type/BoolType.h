#ifndef H9CF18BA3_339E_49A6_9FF2_B51A4195F632
#define H9CF18BA3_339E_49A6_9FF2_B51A4195F632

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<bool V> struct BoolType;

template<>
struct BoolType<true>
{
    enum { Value = true };
};

template<>
struct BoolType<false>
{
    enum { Value = false };
};

using True = BoolType<true>;
using False = BoolType<false>;

TLP_NS_END

#define __true    TLP_NS::True
#define __false   TLP_NS::False

#endif
