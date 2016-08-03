#include <tlp/test/Test.hpp>
#include <tlp/int/IntType.h>
#include <tlp/int/algo/Inc.h>
#include <tlp/int/algo/Dec.h>
#include <tlp/int/algo/Add.h>
#include <tlp/int/algo/Sub.h>
#include <tlp/int/algo/Mul.h>
#include <tlp/int/algo/Div.h>
#include <tlp/int/algo/Mod.h>

FIXTURE(TestInt)
{
    TEST("compare int type")
    {
        ASSERT_EQ(__int(0), __int(0));
        ASSERT_NE(__int(0), __int(1));
    };

    TEST("operator inc on int type")
    {
        ASSERT_EQ(__inc(__int(0)), __int(1));
    };

    TEST("operator dec on int type")
    {
        ASSERT_EQ(__dec(__int(0)), __int(-1));
    };

    TEST("operator add on int type")
    {
        ASSERT_EQ(__add(__int(0), __int(1)), __int(1));
    };

    TEST("operator sub on int type")
    {
        ASSERT_EQ(__sub(__int(0), __int(1)), __int(-1));
    };

    TEST("operator mul on int type")
    {
        ASSERT_EQ(__mul(__int(0), __int(1)), __int(0));
        ASSERT_EQ(__mul(__int(1), __int(10)), __int(10));
        ASSERT_EQ(__mul(__int(10), __int(11)), __int(110));
    };

    TEST("operator div on int type")
    {
        ASSERT_EQ(__div(__int(0), __int(1)), __int(0));
        ASSERT_EQ(__div(__int(10), __int(2)), __int(5));
        ASSERT_EQ(__div(__int(11), __int(2)), __int(5));
    };

    TEST("operator mod on int type")
    {
        ASSERT_EQ(__mod(__int(0), __int(1)), __int(0));
        ASSERT_EQ(__mod(__int(10), __int(2)), __int(0));
        ASSERT_EQ(__mod(__int(11), __int(3)), __int(2));
    };
};
