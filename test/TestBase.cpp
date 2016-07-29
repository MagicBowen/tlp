#include <tlp/test/Test.h>
#include <tlp/base/EmptyType.h>
#include <tlp/base/NullType.h>
#include <tlp/base/algo/Valid.h>

FIXTURE(TestBase)
{
    TEST("null type should not be valid")
    {
        ASSERT_FALSE(__valid(__null()));
    };

    TEST("empty type should be valid")
    {
        ASSERT_TRUE(__valid(__empty()));
    };

    TEST("empty should not be equal to null")
    {
        ASSERT_NE(__empty(), __null());
    };
};
