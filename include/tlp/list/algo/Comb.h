#ifndef HEB9EB0F5_8645_4142_93B8_979041FAAE11
#define HEB9EB0F5_8645_4142_93B8_979041FAAE11

#include <tlp/int/IntType.h>
#include <tlp/list/algo/Length.h>
#include <tlp/list/algo/Map.h>
#include <tlp/list/algo/Append.h>
#include <tlp/bool/algo/IsEqual.h>
#include <tlp/func/SelectFunc.h>

TLP_NS_BEGIN

template<typename TL, typename N> struct Comb;

template<typename Head, typename Tail>
struct Comb<TypeElem<Head, Tail>, IntType<1>>
{
private:
    template<typename T>
    struct ToList
    {
        using Result = typename TypeList<T>::Result;
    };

public:
    using Result = typename Map<TypeElem<Head, Tail>, ToList>::Result;
};

namespace details
{
    template<typename T, typename TL> struct AppendFirst;

    template<typename T, typename Head, typename Tail>
    struct AppendFirst<T, TypeElem<Head, Tail>>
    {
        using Result = TypeElem<T, TypeElem<Head, Tail>>;
    };

    template<typename Head, typename Tail, int N>
    struct CombNormal
    {
    private:
        using TL = TypeElem<Head, Tail>;

        using Temp1 = typename Comb<Tail, IntType<N - 1>>::Result;

        template<typename TL>
        struct JoinHead
        {
            using Result = typename AppendFirst<Head, TL>::Result;
        };

        using Temp = typename Map<Temp1, JoinHead>::Result;

    public:
        using Result = typename Append<Temp, typename Comb<Tail, IntType<N>>::Result>::Result;
    };

    template<typename TL>
    struct CombFull
    {
        using Result = TypeElem<TL, NullType>;
    };
}

template<typename Head, typename Tail, int N>
struct Comb<TypeElem<Head, Tail>, IntType<N>>
{
private:
    using TL = TypeElem<Head, Tail>;

public:
    using Result = typename SelectFunc< typename IsEqual<typename Length<TL>::Result, IntType<N>>::Result
                                      , details::CombFull<TL>
                                      , details::CombNormal<Head, Tail, N>>::Result;
};

TLP_NS_END

#define __comb(...)  typename TLP_NS::Comb<__VA_ARGS__>::Result

#endif
