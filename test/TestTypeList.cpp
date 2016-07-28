#include <tlp/utils/Test.h>
#include <tlp/type/EmptyType.h>
#include <tlp/type/BoolType.h>
#include <tlp/type/IntType.h>
#include <tlp/utils/UniqueName.h>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/Not.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/IsBaseOf.h>
#include <tlp/utils/IsConvertible.h>
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
        ASSERT_VALUE_EQ(__length(__type_list(int, char, short)), 3);
    };

    TEST("get the type by index")
    {
        using List = __type_list(int, char, short, long);

        ASSERT_EQ(__at(List, 3), long);
    };

    TEST("get the index of type")
    {
        using List = __type_list(int, char, short, long);

        ASSERT_VALUE_EQ(__index_of(List, short), 2);
    };

    TEST("get the index of the none existed type")
    {
        using List = __type_list(int, short, long);

        ASSERT_VALUE_EQ(__index_of(List, char), -1);
    };

    TEST("compare two list")
    {
        using List1 = __type_list(int, short, long);
        using List2 = __type_list(int, short);

        ASSERT_NE(List1, List2);
    };

    TEST("append a type t a list")
    {
        using List = __append(__type_list(int, short), long);
        using Expected = __type_list(int, short, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("erase a type from a list")
    {
        using List = __erase(__type_list(int, short, long), short);
        using Expected = __type_list(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("erase all the same type from a list")
    {
        using List = __erase_all(__type_list(short, int, short, long, short), short);
        using Expected = __type_list(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("remove all the duplicated type from a list")
    {
        using List = __unique(__type_list(short, int, short, int, long, short, long));
        using Expected = __type_list(short, int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("replace a type in a given list")
    {
        using List = __replace(__type_list(int, short, long, short), short, int);
        using Expected = __type_list(int, int, long, short);

        ASSERT_EQ(List, Expected);
    };

    TEST("replace all the same type in a given list")
    {
        using List = __replace_all(__type_list(int, short, long, short), short, int);
        using Expected = __type_list(int, int, long, int);

        ASSERT_EQ(List, Expected);
    };
};

FIXTURE(TestAdvancedAlgo)
{
    template<typename T> struct LargerThan2Bytes{ enum { Value = sizeof(T) > 2 }; };

    TEST("any one of the list satisfied the given prediction")
    {
        ASSERT_TRUE(__any(__type_list(char, short, int), LargerThan2Bytes));
    };

    TEST("none of the list satisfied the given prediction")
    {
        ASSERT_FALSE(__any(__type_list(char, short), LargerThan2Bytes));
    };

    TEST("all of the list satisfied the given prediction")
    {
        ASSERT_TRUE(__all(__type_list(int, long), LargerThan2Bytes));
    };

    TEST("any of the type in list not satisfied the given prediction")
    {
        ASSERT_FALSE(__all(__type_list(int, long, short), LargerThan2Bytes));
    };

    TEST("filter the list by the given prediction")
    {
        using List = __filter(__type_list(int, char, short, long), LargerThan2Bytes);
        using Expected = __type_list(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST("map the list by the given transform function")
    {
        template<typename T> struct TypeSize { using Result = __int(sizeof(T)); };

        using List = __map(__type_list(int, char, short, long), TypeSize);
        using Expected = __type_list(__int(4), __int(1), __int(2), __int(8));

        ASSERT_EQ(List, Expected);
    };

    TEST("fold the list by the given accumulate function")
    {
        template<typename Acc, typename T>
        struct SumSize { using Result = __int(Acc::Value + sizeof(T)); };

        using List = __type_list(int, char, long);
        using Result = __fold(List, __int(0), SumSize);

        ASSERT_VALUE_EQ(Result::Value, 13);
    };

    TEST("sort a list by the given size compared rule")
    {
        template<typename T, typename U>
        using SizeLarger = TLP_NS::IfThenElse<(sizeof(T) > sizeof(U)), T, U>;

        using List = __type_list(char, long, short, long, int);
        using Expected = __type_list(long, long, int, short, char);

        ASSERT_EQ(__sort(List, SizeLarger), Expected);
    };

    TEST("sort a list by type inherit relationship")
    {
        struct Base{};
        struct Leaf1 : Base {};
        struct Branch : Base {};
        struct Leaf2 : Branch {};
        struct Leaf3 : Branch {};

        template<typename T, typename U>
        using TypeUpper = TLP_NS::IfThenElse<__is_base_of(T, U), T, U>;

        using List = __type_list(Branch, Leaf2, Base, Leaf3, Leaf1);
        using Expected = __type_list(Base, Branch, Leaf2, Leaf3, Leaf1);

        ASSERT_EQ(__sort(List, TypeUpper), Expected);
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

        ASSERT_TRUE(__is_base_of(Holder<char, __empty>, Aggregator));
    };
};
