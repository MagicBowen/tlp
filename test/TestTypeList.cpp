#include <cut/cut.hpp>
#include <tlp/core/TypeList.h>
#include <tlp/algo/IsEqual.h>
#include <tlp/algo/Length.h>
#include <tlp/algo/IndexOf.h>
#include <tlp/algo/TypeAt.h>
#include <tlp/algo/Append.h>
#include <tlp/algo/Erase.h>
#include <tlp/algo/EraseAll.h>
#include <tlp/algo/Unique.h>

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
        using List1 = TYPE_LIST(int, short, long);
        using List2 = APPEND(TYPE_LIST(int, short), long);

        ASSERT_THAT(IS_EQUAL(List1, List2), be_true());
    }

    TEST("erase a type from a list")
    {
        using List1 = TYPE_LIST(int, long);
        using List2 = ERASE(TYPE_LIST(int, short, long), short);

        ASSERT_THAT(IS_EQUAL(List1, List2), be_true());
    }

    TEST("erase all the same type from a list")
    {
        using List1 = TYPE_LIST(int, long);
        using List2 = ERASE_ALL(TYPE_LIST(short, int, short, long, short), short);

        ASSERT_THAT(IS_EQUAL(List1, List2), be_true());
    }

    TEST("remove all the duplicated type from a list")
    {
        using List1 = TYPE_LIST(short, int, long);
        using List2 = UNIQUE(TYPE_LIST(short, int, short, int, long, short, long));

        ASSERT_THAT(IS_EQUAL(List1, List2), be_true());
    }
};
