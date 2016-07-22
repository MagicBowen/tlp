#include <cut/cut.hpp>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/IfThenElse.h>

USING_CUM_NS

FIXTURE(TestUtils)
{
    TEST("compare types equal")
    {
        ASSERT_THAT(IS_EQUAL(int, int), be_true());
    }

    TEST("compare types unequal")
    {
        ASSERT_THAT(IS_EQUAL(int, short), be_false());
    }

    TEST("select the true branch")
    {
        using Type = IF_THEN_ELSE((sizeof(int) > sizeof(short)), int, short);

        ASSERT_THAT(IS_EQUAL(Type, int), be_true());
    }

    TEST("select the false branch")
    {
        using Type = IF_THEN_ELSE((sizeof(int) < sizeof(short)), int, short);

        ASSERT_THAT(IS_EQUAL(Type, short), be_true());
    }
};
