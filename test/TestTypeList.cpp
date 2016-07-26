#include <tlp/utils/Test.h>
#include <tlp/type/IntType.h>
#include <tlp/type/EmptyType.h>
#include <tlp/list/TypeList.h>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/IsBaseOf.h>
#include <tlp/utils/Print.h>
#include <tlp/algo/Length.h>
#include <tlp/algo/IndexOf.h>
#include <tlp/algo/TypeAt.h>
#include <tlp/algo/Append.h>
#include <tlp/algo/Erase.h>
#include <tlp/algo/EraseAll.h>
#include <tlp/algo/Unique.h>
#include <tlp/algo/Replace.h>
#include <tlp/algo/ReplaceAll.h>
#include <tlp/algo/Any.h>
#include <tlp/algo/All.h>
#include <tlp/algo/Filter.h>
#include <tlp/algo/Map.h>
#include <tlp/algo/Fold.h>
#include <tlp/algo/Sort.h>
#include <tlp/algo/ScatterInherits.h>
#include <tlp/algo/LinearInherits.h>

FIXTURE(TestBaseAlgo)
{
    TEST("get the length of type list")
    {
        ASSERT_VALUE_EQ(LENGTH(TYPE_LIST(int, char, short)), 3);
    };

    TEST("get the type by index")
    {
        using List = TYPE_LIST(int, char, short, long);

        ASSERT_EQ(TYPE_AT(List, 3), long);
    };

    TEST("get the index of type")
    {
        using List = TYPE_LIST(int, char, short, long);

        ASSERT_VALUE_EQ(INDEX_OF(List, short), 2);
    };

    TEST("get the index of the none existed type")
    {
        using List = TYPE_LIST(int, short, long);

        ASSERT_VALUE_EQ(INDEX_OF(List, char), -1);
    };

    TEST("compare two list")
    {
        using List1 = TYPE_LIST(int, short, long);
        using List2 = TYPE_LIST(int, short);

        ASSERT_NE(List1, List2);
    };

    TEST("append a type t a list")
    {
        using List = APPEND(TYPE_LIST(int, short), long);
        using Expected = TYPE_LIST(int, short, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("erase a type from a list")
    {
        using List = ERASE(TYPE_LIST(int, short, long), short);
        using Expected = TYPE_LIST(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("erase all the same type from a list")
    {
        using List = ERASE_ALL(TYPE_LIST(short, int, short, long, short), short);
        using Expected = TYPE_LIST(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("remove all the duplicated type from a list")
    {
        using List = UNIQUE(TYPE_LIST(short, int, short, int, long, short, long));
        using Expected = TYPE_LIST(short, int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("replace a type in a given list")
    {
        using List = REPLACE(TYPE_LIST(int, short, long, short), short, int);
        using Expected = TYPE_LIST(int, int, long, short);

        ASSERT_EQ(List, Expected);
    };

    TEST("replace all the same type in a given list")
    {
        using List = REPLACE_ALL(TYPE_LIST(int, short, long, short), short, int);
        using Expected = TYPE_LIST(int, int, long, int);

        ASSERT_EQ(List, Expected);
    };
};

FIXTURE(TestAdvancedAlgo)
{
    using TLP_NS::IfThenElse;
    using TLP_NS::IsBaseOf;
    using TLP_NS::IntType;

    template<typename T> struct LargerThan2Bytes{ enum { Value = sizeof(T) > 2 }; };

    TEST("any one of the list satisfied the given prediction")
    {
        ASSERT_TRUE(ANY(TYPE_LIST(char, short, int), LargerThan2Bytes));
    };

    TEST("none of the list satisfied the given prediction")
    {
        ASSERT_FALSE(ANY(TYPE_LIST(char, short), LargerThan2Bytes));
    };

    TEST("all of the list satisfied the given prediction")
    {
        ASSERT_TRUE(ALL(TYPE_LIST(int, long), LargerThan2Bytes));
    };

    TEST("any of the type in list not satisfied the given prediction")
    {
        ASSERT_FALSE(ALL(TYPE_LIST(int, long, short), LargerThan2Bytes));
    };

    TEST("filter the list by the given prediction")
    {
        using List = FILTER(TYPE_LIST(int, char, short, long), LargerThan2Bytes);
        using Expected = TYPE_LIST(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("map the list by the given transform function")
    {
        template<typename T> struct TypeSize { using Result = IntType<sizeof(T)>; };

        using List = MAP(TYPE_LIST(int, char, short, long), TypeSize);
        using Expected = TYPE_LIST(IntType<4>, IntType<1>, IntType<2>, IntType<8>);

        ASSERT_EQ(List, Expected);
    };

    TEST("fold the list by the given accumulate function")
    {
        template<typename Acc, typename T>
        struct SumSize { using Result = IntType<Acc::Value + sizeof(T)>; };

        using List = TYPE_LIST(int, char, long);
        using Result = FOLD(List, IntType<0>, SumSize);

        ASSERT_VALUE_EQ(Result::Value, 13);
    };

    TEST("sort a list by the given size compared rule")
    {
        template<typename T, typename U>
        struct SizeLarger
        {
            using Result = typename IfThenElse<(sizeof(T) > sizeof(U)), T, U>::Result;
        };

        using List = TYPE_LIST(char, long, short, long, int);
        using Expected = TYPE_LIST(long, long, int, short, char);

        ASSERT_EQ(SORT(List, SizeLarger), Expected);
    };

    TEST("sort a list by type inherit relationship")
    {
        struct Base{};
        struct Leaf1 : Base {};
        struct Branch : Base {};
        struct Leaf2 : Branch {};
        struct Leaf3 : Branch {};

        template<typename T, typename U>
        struct TypeUpper
        {
            using Result = typename IfThenElse<IsBaseOf<T, U>::Value, T, U>::Result;
        };

        using List = TYPE_LIST(Branch, Leaf2, Base, Leaf3, Leaf1);
        using Expected = TYPE_LIST(Base, Branch, Leaf2, Leaf3, Leaf1);

        ASSERT_EQ(SORT(List, TypeUpper), Expected);
    };
};

FIXTURE(TestInheritsAggregateAlgo)
{
    using TLP_NS::EmptyType;

    TEST("scatter inherits from a type list")
    {
        template<typename T> struct Holder { T t; };
        using Aggregator = SCATTER_INHERITS(TYPE_LIST(int, short, char), Holder);

        ASSERT_TRUE(IS_BASE_OF(Holder<int>, Aggregator));
        ASSERT_FALSE(IS_BASE_OF(Holder<int>, Holder<short>));
    };

    TEST("linear inherits from a type list")
    {
        template<typename T, typename Base> struct Holder : Base { T t; };
        using Aggregator = LINEAR_INHERITS(TYPE_LIST(int, short, char), Holder);

        ASSERT_TRUE(IS_BASE_OF(Holder<char, EmptyType>, Aggregator));
    };
};
