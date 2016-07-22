#include <cut/cut.hpp>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/Convertible.h>
#include <tlp/utils/Inherits.h>

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

    TEST("try convert the convertible types")
    {
        ASSERT_THAT(CONVERTIBLE(char, int),    be_true());
        ASSERT_THAT(CONVERTIBLE(char, void*),  be_false());
        ASSERT_THAT(CONVERTIBLE(char*, void*), be_true());
    }

    TEST("try convert the hierarchy types")
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_THAT(CONVERTIBLE(Base, Derived),    be_false());
        ASSERT_THAT(CONVERTIBLE(Derived, Base),    be_true());

        ASSERT_THAT(CONVERTIBLE(Base*, Derived*),  be_false());
        ASSERT_THAT(CONVERTIBLE(Derived*, Base*),  be_true());
    }

    TEST("try convert the both convertible types")
    {
        ASSERT_THAT(BOTH_CONVERTIBLE(short, int),   be_true());
        ASSERT_THAT(BOTH_CONVERTIBLE(char*, void*), be_false());
    }

    TEST("try test the super sub types")
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_THAT(INHERITS(int, char),       be_false());
        ASSERT_THAT(INHERITS(void*, char*),    be_false());
        ASSERT_THAT(INHERITS(Base, Derived),   be_true());
        ASSERT_THAT(INHERITS(Derived, Base),   be_false());
    }
};
