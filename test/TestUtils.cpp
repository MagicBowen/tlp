#include <tlp/utils/Test.h>
#include <tlp/utils/UniqueName.h>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/Not.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/IsBaseOf.h>
#include <tlp/utils/IsConvertible.h>
#include <tlp/utils/Print.h>

FIXTURE(TestUtils)
{
    TEST("compare types equal")
    {
        ASSERT_TRUE(__is_eq(int, int));
    };

    TEST("compare types unequal")
    {
        ASSERT_FALSE(__is_eq(int, short));
    };

    TEST("opposite of a prediction")
    {
        template<typename T> struct Pred { enum { Value = true }; };

        ASSERT_FALSE(__not(Pred)<int>::Value);
    };

    TEST("select the true branch")
    {
        using Type = __if((sizeof(int) > sizeof(short)), int, short);

        ASSERT_EQ(Type, int);
    };

    TEST("select the false branch")
    {
        using Type = __if((sizeof(int) < sizeof(short)), int, short);

        ASSERT_EQ(Type, short);
    };

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
