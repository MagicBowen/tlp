#include <tlp/test/Test.h>
#include <tlp/traits/IsConvertible.h>
#include <tlp/traits/IsBaseOf.h>

FIXTURE(TestTraits)
{
    TEST("try convert the convertible types")
    {
        ASSERT_TRUE(__is_convertible(char, int));
        ASSERT_FALSE(__is_convertible(char, void*));
        ASSERT_TRUE(__is_convertible(char*, void*));
    };

    TEST("try convert the hierarchy types")
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_FALSE(__is_convertible(Base, Derived));
        ASSERT_TRUE(__is_convertible(Derived, Base));

        ASSERT_FALSE(__is_convertible(Base*, Derived*));
        ASSERT_TRUE(__is_convertible(Derived*, Base*));
    };

    TEST("try convert the both convertible types")
    {
        ASSERT_TRUE(__is_both_convertible(short, int));
        ASSERT_FALSE(__is_both_convertible(char*, void*));
    };

    TEST("try test inherits relationship of the super sub types")
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_FALSE(__is_base_of(int, char));
        ASSERT_FALSE(__is_base_of(void*, char*));
        ASSERT_TRUE(__is_base_of(Base, Derived));
        ASSERT_FALSE(__is_base_of(Derived, Base));
    };
};
