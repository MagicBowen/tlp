#include <tlp/utils/Test.h>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/Not.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/IsConvertible.h>
#include <tlp/utils/IsBaseOf.h>

FIXTURE(TestUtils)
{
    TEST("compare types equal")
    {
        ASSERT_TRUE(IS_EQUAL(int, int));
    };

    TEST("compare types unequal")
    {
        ASSERT_FALSE(IS_EQUAL(int, short));
    };

    TEST("opposite of a prediction")
    {
        template<typename T> struct Pred { enum { Value = true }; };

        ASSERT_FALSE(TLP_NS::Not<Pred>::Result<int>::Value);
    };

    TEST("select the true branch")
    {
        using Type = IF_THEN_ELSE((sizeof(int) > sizeof(short)), int, short);

        ASSERT_EQ(Type, int);
    };

    TEST("select the false branch")
    {
        using Type = IF_THEN_ELSE((sizeof(int) < sizeof(short)), int, short);

        ASSERT_EQ(Type, short);
    };

    TEST("try convert the convertible types")
    {
        ASSERT_TRUE(IS_CONVERTIBLE(char, int));
        ASSERT_FALSE(IS_CONVERTIBLE(char, void*));
        ASSERT_TRUE(IS_CONVERTIBLE(char*, void*));
    };

    TEST("try convert the hierarchy types")
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_FALSE(IS_CONVERTIBLE(Base, Derived));
        ASSERT_TRUE(IS_CONVERTIBLE(Derived, Base));

        ASSERT_FALSE(IS_CONVERTIBLE(Base*, Derived*));
        ASSERT_TRUE(IS_CONVERTIBLE(Derived*, Base*));
    };

    TEST("try convert the both convertible types")
    {
        ASSERT_TRUE(IS_BOTH_CONVERTIBLE(short, int));
        ASSERT_FALSE(IS_BOTH_CONVERTIBLE(char*, void*));
    };

    TEST("try test inherits relationship of the super sub types")
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_FALSE(IS_BASE_OF(int, char));
        ASSERT_FALSE(IS_BASE_OF(void*, char*));
        ASSERT_TRUE(IS_BASE_OF(Base, Derived));
        ASSERT_FALSE(IS_BASE_OF(Derived, Base));
    };
};
