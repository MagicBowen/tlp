#ifndef H9CF18BA3_339E_49A6_9FF2_B51A4195F632
#define H9CF18BA3_339E_49A6_9FF2_B51A4195F632

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<bool V> struct BoolType;

template<>
struct BoolType<true>
{
    enum { Value = true };
    using Result = BoolType<true>;
};

template<>
struct BoolType<false>
{
    enum { Value = false };
    using Result = BoolType<false>;
};

using TrueType = BoolType<true>;
using FalseType = BoolType<false>;

TLP_NS_END

#define __bool(...)    typename TLP_NS::BoolType<__VA_ARGS__>::Result
#define __true()       typename TLP_NS::TrueType::Result
#define __false()      typename TLP_NS::FalseType::Result

#endif
