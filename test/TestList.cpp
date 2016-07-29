#include <tlp/test/Test.h>
#include <tlp/base/EmptyType.h>
#include <tlp/base/algo/Valid.h>
#include <tlp/bool/BoolType.h>
#include <tlp/bool/algo/IsEqual.h>
#include <tlp/bool/algo/Select.h>
#include <tlp/int/IntType.h>
#include <tlp/func/Negative.h>
#include <tlp/traits/IsBaseOf.h>
#include <tlp/traits/IsConvertible.h>
#include <tlp/list/EmptyList.h>
#include <tlp/list/algo/ValueList.h>
#include <tlp/list/algo/TypeList.h>
#include <tlp/list/algo/Length.h>
#include <tlp/list/algo/TypeAt.h>
#include <tlp/list/algo/IndexOf.h>
#include <tlp/list/algo/Append.h>
#include <tlp/list/algo/Erase.h>
#include <tlp/list/algo/EraseAll.h>
#include <tlp/list/algo/Unique.h>
#include <tlp/list/algo/Replace.h>
#include <tlp/list/algo/ReplaceAll.h>
#include <tlp/list/algo/Any.h>
#include <tlp/list/algo/All.h>
#include <tlp/list/algo/Filter.h>
#include <tlp/list/algo/Map.h>
#include <tlp/list/algo/Fold.h>
#include <tlp/list/algo/Sort.h>
#include <tlp/list/algo/ScatterInherits.h>
#include <tlp/list/algo/LinearInherits.h>

FIXTURE(TestListBaseAlgo)
{
    TEST("compare two list")
    {
        ASSERT_NE(__empty_list(), __type_list(int, char));
        ASSERT_NE(__type_list(int), __type_list(int, char));
        ASSERT_EQ(__value_list(0, 1), __type_list(__int(0), __int(1)));
    };

    TEST("the length of empty list should be zero")
    {
        ASSERT_EQ(__length(__empty_list()), __int(0));
    };

    TEST("get the length of type list")
    {
        ASSERT_EQ(__length(__type_list(int, char, short)), __int(3));
    };

    TEST("get null from empty list by index")
    {
        ASSERT_INVALID(__at(__empty_list(), __int(2)));
    };

    TEST("get null from list by overflow index")
    {
        using List = __type_list(int, char, short, long);

        ASSERT_INVALID(__at(List, __int(4)));
    };

    TEST("get the type by zero index")
    {
        using List = __type_list(int, char, short, long);

        ASSERT_EQ(__at(List, __int(0)), int);
    };

    TEST("get the type by index")
    {
        using List = __type_list(int, char, short, long);

        ASSERT_EQ(__at(List, __int(3)), long);
    };

    TEST("get the index of empty list")
    {
        ASSERT_INVALID(__index_of(__empty_list(), int));
    };

    TEST("get the index of the none existed type")
    {
        using List = __type_list(int, char);

        ASSERT_INVALID(__index_of(List, short));
    };

    TEST("get the index of the none existed type")
    {
        using List = __type_list(int, short, long);

        ASSERT_EQ(__index_of(List, long), __int(2));
    };

    TEST("append a type to an empty list")
    {
        ASSERT_EQ(__append(__empty_list(), char), __type_list(char));
    };

    TEST("append a list to an empty list")
    {
        using List = __type_list(int, char);

        ASSERT_EQ(__append(__empty_list(), List), List);
    };

    TEST("append an empty list_to a list")
    {
        using List = __type_list(int, char);

        ASSERT_EQ(__append(List, __empty_list()), List);
    };

    TEST("append a type to a list")
    {
        using List = __type_list(int, short);
        using Expected = __type_list(int, short, long);

        ASSERT_EQ(__append(List, long), Expected);
    };

    TEST("append a list to a list")
    {
        using List = __type_list(int, short);
        using Expected = __type_list(int, short, char, long);

        ASSERT_EQ(__append(List, __type_list(char, long)), Expected);
    };

    TEST("erase a type from an empty list")
    {
        ASSERT_EQ(__erase(__empty_list(), short), __empty_list());
    };

    TEST("erase an none existed type from a list")
    {
        using List = __type_list(int, short, long);

        ASSERT_EQ(__erase(List, char), List);
    };

    TEST("erase a type from a list")
    {
        using List = __type_list(int, short, long);
        using Expected = __type_list(int, long);

        ASSERT_EQ(__erase(List, short), Expected);
    };

    TEST("erase all the same type from a list")
    {
        using List = __type_list(short, int, short, long, short);
        using Expected = __type_list(int, long);

        ASSERT_EQ(__erase_all(List, short), Expected);
    };

    TEST("remove all the duplicated type from a list")
    {
        using List = __type_list(short, int, short, int, long, short, long);
        using Expected = __type_list(short, int, long);

        ASSERT_EQ(__unique(List), Expected);
    };

    TEST("replace a type in a given list")
    {
        using List = __type_list(int, short, long, short);
        using Expected = __type_list(int, int, long, short);

        ASSERT_EQ(__replace(List, short, int), Expected);
    };

    TEST("replace all the same type in a given list")
    {
        using List = __type_list(int, short, long, short);
        using Expected = __type_list(int, int, long, int);

        ASSERT_EQ(__replace_all(List, short, int), Expected);
    };
};

FIXTURE(TestAdvancedAlgo)
{
    template<typename T> struct IsLargerThan2Bytes{ using Result = __bool((sizeof(T) > 2)); };

    TEST("any one of the list satisfied the given prediction")
    {
        ASSERT_TRUE(__any(__type_list(char, short, int), IsLargerThan2Bytes));
    };

    TEST("none of the list satisfied the given prediction")
    {
        ASSERT_FALSE(__any(__type_list(char, short), IsLargerThan2Bytes));
    };

    TEST("all of the list satisfied the given prediction")
    {
        ASSERT_TRUE(__all(__type_list(int, long), IsLargerThan2Bytes));
    };

    TEST("any of the type in list not satisfied the given prediction")
    {
        ASSERT_FALSE(__all(__type_list(int, long, short), IsLargerThan2Bytes));
    };

    TEST("filter the list by the given prediction")
    {
        using List = __type_list(int, char, short, long);
        using Expected = __type_list(int, long);

        ASSERT_EQ(__filter(List, IsLargerThan2Bytes), Expected);
    };

    TEST("map the list to it's size value list")
    {
        template<typename T> struct TypeSize { using Result = __int(sizeof(T)); };

        using List = __type_list(int, char, short, long);
        using Expected = __value_list(4, 1, 2, 8);

        ASSERT_EQ(__map(List, TypeSize), Expected);
    };

    TEST("map the type in list to it's twice pointer type list")
    {
        template<typename T> struct TransToPointer { using Result = T*; };

        using List = __type_list(int, const char);
        using Expected = __type_list(int**, const char**);

        ASSERT_EQ(__map(__map(List, TransToPointer), TransToPointer), Expected);
    };

    TEST("fold the list by the given accumulate function")
    {
        template<typename Acc, typename T>
        struct SumSize { using Result = __plus(Acc, __int(sizeof(T))); };

        using List = __type_list(int, char, long);

        ASSERT_EQ(__fold(List, __int(0), SumSize), __int(13));
    };

    TEST("sort a list by the given size compared rule")
    {
        template<typename T, typename U>
        using LargerSizeType = TLP_NS::Select<__bool((sizeof(T) > sizeof(U))), T, U>;

        using List = __type_list(char, long, short, long, int);
        using Expected = __type_list(long, long, int, short, char);

        ASSERT_EQ(__sort(List, LargerSizeType), Expected);
    };

    TEST("sort a list by type inherit relationship")
    {
        struct Base{};
        struct Leaf1 : Base {};
        struct Branch : Base {};
        struct Leaf2 : Branch {};
        struct Leaf3 : Branch {};

        template<typename T, typename U>
        using Supper = TLP_NS::Select<__is_base_of(T, U), T, U>;

        using List = __type_list(Branch, Leaf2, Base, Leaf3, Leaf1);
        using Expected = __type_list(Base, Branch, Leaf2, Leaf3, Leaf1);

        ASSERT_EQ(__sort(List, Supper), Expected);
    };
};

FIXTURE(TestInheritsAggregateAlgo)
{
    TEST("scatter inherits from a type list")
    {
        template<typename T> struct Holder { T t; };
        using Aggregator = __scatter_inherits(__type_list(int, short, char), Holder);

        ASSERT_TRUE(__is_base_of(Holder<int>, Aggregator));
        ASSERT_FALSE(__is_base_of(Holder<int>, Holder<short>));
    };

    TEST("linear inherits from a type list")
    {
        template<typename T, typename Base> struct Holder : Base { T t; };
        using Aggregator = __linear_inherits(__type_list(int, short, char), Holder);

        ASSERT_TRUE(__is_base_of(Holder<char, __empty()>, Aggregator));
    };
};
