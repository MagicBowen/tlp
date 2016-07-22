#include <cut/cut.hpp>
#include <tlp/base/IntType.h>
#include <tlp/list/TypeList.h>
#include <tlp/utils/IsEqual.h>
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

using tlp::IntType;

USING_CUM_NS

FIXTURE(TestTypeList)
{
    TEST("get the size of type list")
    {
        ASSERT_THAT(LENGTH(TYPE_LIST(int, char, short)), eq(3));
    }

    TEST("get the type by index")
    {
        using List = TYPE_LIST(int, char, short, long);
        ASSERT_THAT(sizeof(TYPE_AT(List, 3)), eq(8));
    }

    TEST("get the index of type")
    {
        using List = TYPE_LIST(int, char, short, long);
        ASSERT_THAT(INDEX_OF(List, short), eq(2));
    }

    TEST("get the index of the none existed type")
    {
        using List = TYPE_LIST(int, short, long);
        ASSERT_THAT(INDEX_OF(List, char), eq(-1));
    }

    TEST("compare two list")
    {
        using List1 = TYPE_LIST(int, short, long);
        using List2 = TYPE_LIST(int, short);

        ASSERT_THAT(IS_EQUAL(List1, List2), be_false());
    }

    TEST("append a type to a list")
    {
        using List = APPEND(TYPE_LIST(int, short), long);
        using Expected = TYPE_LIST(int, short, long);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    TEST("erase a type from a list")
    {
        using List = ERASE(TYPE_LIST(int, short, long), short);
        using Expected = TYPE_LIST(int, long);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    TEST("erase all the same type from a list")
    {
        using List = ERASE_ALL(TYPE_LIST(short, int, short, long, short), short);
        using Expected = TYPE_LIST(int, long);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    TEST("remove all the duplicated type from a list")
    {
        using List = UNIQUE(TYPE_LIST(short, int, short, int, long, short, long));
        using Expected = TYPE_LIST(short, int, long);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    TEST("replace type in a list")
    {
        using List = REPLACE(TYPE_LIST(int, short, long, short), short, int);
        using Expected = TYPE_LIST(int, int, long, short);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    TEST("replace all the same type in a list")
    {
        using List = REPLACE_ALL(TYPE_LIST(int, short, long, short), short, int);
        using Expected = TYPE_LIST(int, int, long, int);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    template<typename T> struct LargerThan2Bytes{ enum { Value = sizeof(T) > 2 }; };

    TEST("any one of the list satisfied prediction")
    {
        ASSERT_THAT(ANY(TYPE_LIST(char, short, int), LargerThan2Bytes), be_true());
    }

    TEST("none of the list satisfied prediction")
    {
        ASSERT_THAT(ANY(TYPE_LIST(char, short), LargerThan2Bytes), be_false());
    }

    TEST("all of the list satisfied prediction")
    {
        ASSERT_THAT(ALL(TYPE_LIST(int, long), LargerThan2Bytes), be_true());
    }

    TEST("any of the type in list not satisfied prediction")
    {
        ASSERT_THAT(ALL(TYPE_LIST(int, long, short), LargerThan2Bytes), be_false());
    }

    TEST("filter the list")
    {
        using List = FILTER(TYPE_LIST(int, char, short, long), LargerThan2Bytes);
        using Expected = TYPE_LIST(int, long);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }

    template<typename T> struct TypeSize { using Result = IntType<sizeof(T)>; };

    TEST("map the list")
    {
        using List = MAP(TYPE_LIST(int, char, short, long), TypeSize);
        using Expected = TYPE_LIST(IntType<4>, IntType<1>, IntType<2>, IntType<8>);

        ASSERT_THAT(IS_EQUAL(List, Expected), be_true());
    }
};
