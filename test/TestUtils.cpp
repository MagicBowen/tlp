#include <tlp/utils/Test.h>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/Not.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/Convertible.h>
#include <tlp/utils/InheritsFrom.h>

FIXTURE(TestUtils)
{
    TEST(compare_types_equal)
    {
        ASSERT_TRUE(IS_EQUAL(int, int));
    };

    TEST(compare_types_unequal)
    {
        ASSERT_FALSE(IS_EQUAL(int, short));
    };

    TEST(opposite_of_a_prediction)
    {
        template<typename T> struct Pred { enum { Value = true }; };

        ASSERT_FALSE(TLP_NS::Not<Pred>::Result<int>::Value);
    };

    TEST(select_the_true_branch)
    {
        using Type = IF_THEN_ELSE((sizeof(int) > sizeof(short)), int, short);

        ASSERT_EQ(Type, int);
    };

    TEST(select_the_false_branch)
    {
        using Type = IF_THEN_ELSE((sizeof(int) < sizeof(short)), int, short);

        ASSERT_EQ(Type, short);
    };

    TEST(try_convert_the_convertible_types)
    {
        ASSERT_TRUE(CONVERTIBLE(char, int));
        ASSERT_FALSE(CONVERTIBLE(char, void*));
        ASSERT_TRUE(CONVERTIBLE(char*, void*));
    };

    TEST(try_convert_the_hierarchy_types)
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_FALSE(CONVERTIBLE(Base, Derived));
        ASSERT_TRUE(CONVERTIBLE(Derived, Base));

        ASSERT_FALSE(CONVERTIBLE(Base*, Derived*));
        ASSERT_TRUE(CONVERTIBLE(Derived*, Base*));
    };

    TEST(try_convert_the_both_convertible_types)
    {
        ASSERT_TRUE(BOTH_CONVERTIBLE(short, int));
        ASSERT_FALSE(BOTH_CONVERTIBLE(char*, void*));
    };

    TEST(try_test_inherits_relationship_of_the_super_sub_types)
    {
        struct Base{};
        struct Derived : Base {};

        ASSERT_FALSE(INHERITS_FROM(int, char));
        ASSERT_FALSE(INHERITS_FROM(void*, char*));
        ASSERT_TRUE(INHERITS_FROM(Base, Derived));
        ASSERT_FALSE(INHERITS_FROM(Derived, Base));
    };
}
