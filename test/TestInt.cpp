#include <tlp/test/Test.h>
#include <tlp/int/IntType.h>
#include <tlp/int/algo/Next.h>
#include <tlp/int/algo/Prev.h>
#include <tlp/int/algo/Plus.h>
#include <tlp/int/algo/Minus.h>
#include <tlp/int/algo/Multi.h>
#include <tlp/int/algo/Div.h>
#include <tlp/int/algo/Mod.h>

FIXTURE(TestInt)
{
    TEST("compare int type")
    {
        ASSERT_EQ(__int(0), __int(0));
        ASSERT_NE(__int(0), __int(1));
    };

    TEST("operator next on int type")
    {
        ASSERT_EQ(__next(__int(0)), __int(1));
    };

    TEST("operator prev on int type")
    {
        ASSERT_EQ(__prev(__int(0)), __int(-1));
    };

    TEST("operator plus on int type")
    {
        ASSERT_EQ(__plus(__int(0), __int(1)), __int(1));
    };

    TEST("operator minus on int type")
    {
        ASSERT_EQ(__minus(__int(0), __int(1)), __int(-1));
    };

    TEST("operator multi on int type")
    {
        ASSERT_EQ(__multi(__int(0), __int(1)), __int(0));
        ASSERT_EQ(__multi(__int(1), __int(10)), __int(10));
        ASSERT_EQ(__multi(__int(10), __int(11)), __int(110));
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
