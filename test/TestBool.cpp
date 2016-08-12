#include <tlp/test/Test.hpp>
#include <tlp/bool/algo/Not.h>
#include <tlp/bool/algo/And.h>
#include <tlp/bool/algo/Or.h>
#include <tlp/bool/algo/IfThenElse.h>

FIXTURE(TestBool)
{
    TEST("true type should be true")
    {
        ASSERT_TRUE(__true());
        ASSERT_EQ(__true(), __bool(true));
        ASSERT_NE(__true(), __bool(false));
    };

    TEST("false type should be false")
    {
        ASSERT_FALSE(__false());
        ASSERT_EQ(__false(), __bool(false));
        ASSERT_NE(__false(), __bool(true));
    };

    TEST("operator not on bool type")
    {
        ASSERT_TRUE(__not(__false()));
        ASSERT_FALSE(__not(__bool(true)));
    };

    TEST("operator and on bool type")
    {
        ASSERT_TRUE(__and(__true(), __true()));
        ASSERT_FALSE(__and(__true(), __false()));
    };

    TEST("operator or on bool type")
    {
        ASSERT_TRUE(__or(__true(), __false()));
        ASSERT_FALSE(__or(__false(), __false()));
    };

    TEST("compose operators on bool type")
    {
        ASSERT_TRUE(__and(__not(__false()), __or(__false(), __or(__bool(0 == 1), __and(__true(), __bool(1 == 1))))));
    };

    TEST("select based on bool type")
    {
        ASSERT_EQ(__if(__true(), int, char), int);
        ASSERT_EQ(__if(__false(), int, char), char);
    };
};
