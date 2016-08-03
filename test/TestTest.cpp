#include <tlp/test/Test.hpp>
#include <tlp/int/IntType.h>
#include <tlp/int/algo/Add.h>
#include <tlp/int/algo/Mul.h>
#include <tlp/func/Forward.h>

FIXTURE(TestSetUp)
{
    SETUP()
    {
        using expected = __int(0);
    };

    TEST("should use variable defined in setup")
    {
        ASSERT_EQ(__int(0), expected);
    };
};

FIXTURE(TestTearDown)
{
    TEARDOWN_BEGIN()
        ASSERT_EQ(__int(0), __test_refer(expected));
    TEARDOWN_END()

    TEST("should use variable defined in setup")
    {
        using expected = __int(0);
    };
};

FIXTURE(TestWithSetUpAndTearDown)
{
    SETUP_BEGIN()
        using Num = __int(2);
    SETUP_END()

    TEARDOWN_BEGIN()
        using Expected = __int(4);
        using Result = __test_invoke(Op, __test_refer(Num), __test_refer(Num));
        ASSERT_EQ(Result, Expected);
    TEARDOWN_END()

    TEST("test 1")
    {
        __func_forward_2(Op, __add(_1, _2));
    };

    TEST("test 2")
    {
        __func_forward_2(Op, __mul(_1, _2));
    };
};
