#include <tlp/utils/Test.h>
#include <tlp/type/IntType.h>
#include <tlp/list/TypeList.h>
#include <tlp/utils/IsEqual.h>
#include <tlp/utils/IfThenElse.h>
#include <tlp/utils/IsBaseOf.h>
#include <tlp/algo/Length.h>
#include <tlp/algo/IndexOf.h>
#include <tlp/algo/TypeAt.h>
#include <tlp/algo/Append.h>
#include <tlp/algo/Erase.h>
#include <tlp/algo/EraseAll.h>
#include <tlp/algo/Unique.h>
#include <tlp/algo/Replace.h>
#include <tlp/algo/ReplaceAll.h>
#include <tlp/algo/Any.h>
#include <tlp/algo/All.h>
#include <tlp/algo/Filter.h>
#include <tlp/algo/Map.h>
#include <tlp/algo/Fold.h>
#include <tlp/algo/Sort.h>

FIXTURE(TestBaseAlgo)
{
    TEST(get_the_length_of_type_list)
    {
        ASSERT_VALUE_EQ(LENGTH(TYPE_LIST(int, char, short)), 3);
    };

    TEST(get_the_type_by_index)
    {
        using List = TYPE_LIST(int, char, short, long);

        ASSERT_EQ(TYPE_AT(List, 3), long);
    };

    TEST(get_the_index_of_type)
    {
        using List = TYPE_LIST(int, char, short, long);

        ASSERT_VALUE_EQ(INDEX_OF(List, short), 2);
    };

    TEST(get_the_index_of_the_none_existed_type)
    {
        using List = TYPE_LIST(int, short, long);

        ASSERT_VALUE_EQ(INDEX_OF(List, char), -1);
    };

    TEST(compare_two_list)
    {
        using List1 = TYPE_LIST(int, short, long);
        using List2 = TYPE_LIST(int, short);

        ASSERT_NE(List1, List2);
    };

    TEST(append_a_type_t_a_list)
    {
        using List = APPEND(TYPE_LIST(int, short), long);
        using Expected = TYPE_LIST(int, short, long);

        ASSERT_EQ(List, Expected);
    };

    TEST(erase_a_type_from_a_list)
    {
        using List = ERASE(TYPE_LIST(int, short, long), short);
        using Expected = TYPE_LIST(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST(erase_all_the_same_type_from_a_list)
    {
        using List = ERASE_ALL(TYPE_LIST(short, int, short, long, short), short);
        using Expected = TYPE_LIST(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST(remove_all_the_duplicated_type_from_a_list)
    {
        using List = UNIQUE(TYPE_LIST(short, int, short, int, long, short, long));
        using Expected = TYPE_LIST(short, int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST(replace_type_in_a_list)
    {
        using List = REPLACE(TYPE_LIST(int, short, long, short), short, int);
        using Expected = TYPE_LIST(int, int, long, short);

        ASSERT_EQ(List, Expected);
    };

    TEST(replace_all_the_same_type_in_a_list)
    {
        using List = REPLACE_ALL(TYPE_LIST(int, short, long, short), short, int);
        using Expected = TYPE_LIST(int, int, long, int);

        ASSERT_EQ(List, Expected);
    };
}

FIXTURE(TestAdvancedAlgo)
{
    using tlp::IfThenElse;
    using tlp::IsBaseOf;
    using tlp::IntType;

    template<typename T> struct LargerThan2Bytes{ enum { Value = sizeof(T) > 2 }; };

    TEST(any_one_of_the_list_satisfied_the_given_prediction)
    {
        ASSERT_TRUE(ANY(TYPE_LIST(char, short, int), LargerThan2Bytes));
    };

    TEST(none_of_the_list_satisfied_the_given_prediction)
    {
        ASSERT_FALSE(ANY(TYPE_LIST(char, short), LargerThan2Bytes));
    };

    TEST(all_of_the_list_satisfied_the_given_prediction)
    {
        ASSERT_TRUE(ALL(TYPE_LIST(int, long), LargerThan2Bytes));
    };

    TEST(any_of_the_type_in_list_not_satisfied_the_given_prediction)
    {
        ASSERT_FALSE(ALL(TYPE_LIST(int, long, short), LargerThan2Bytes));
    };

    TEST(filter_the_list_by_the_given_prediction)
    {
        using List = FILTER(TYPE_LIST(int, char, short, long), LargerThan2Bytes);
        using Expected = TYPE_LIST(int, long);

        ASSERT_EQ(List, Expected);
    };

    TEST(map_the_list_by_the_given_transform_function)
    {
        template<typename T> struct TypeSize { using Result = IntType<sizeof(T)>; };

        using List = MAP(TYPE_LIST(int, char, short, long), TypeSize);
        using Expected = TYPE_LIST(IntType<4>, IntType<1>, IntType<2>, IntType<8>);

        ASSERT_EQ(List, Expected);
    };

    TEST(fold_the_list_by_the_given_accumulate_function)
    {
        template<typename T, typename U>
        struct SumSize { using Result = IntType<T::Value + sizeof(U)>; };

        using List = TYPE_LIST(int, char, long);
        using Result = FOLD(List, IntType<0>, SumSize);

        ASSERT_VALUE_EQ(Result::Value, 13);
    };

    TEST(sort_a_list_by_the_given_size_compared_rule)
    {
        template<typename T, typename U>
        struct SizeLarger
        {
            using Result = typename IfThenElse<(sizeof(T) > sizeof(U)), T, U>::Result;
        };

        using List = TYPE_LIST(char, long, short, long, int);
        using Expected = TYPE_LIST(long, long, int, short, char);

        ASSERT_EQ(SORT(List, SizeLarger), Expected);
    };

    TEST(sort_a_list_by_type_inherit_relationship)
    {
        struct Base{};
        struct Leaf1 : Base {};
        struct Branch : Base {};
        struct Leaf2 : Branch {};
        struct Leaf3 : Branch {};

        template<typename T, typename U>
        struct TypeUpper
        {
            using Result = typename IfThenElse<IsBaseOf<T, U>::Value, T, U>::Result;
        };

        using List = TYPE_LIST(Branch, Leaf2, Base, Leaf3, Leaf1);
        using Expected = TYPE_LIST(Base, Branch, Leaf2, Leaf3, Leaf1);

        ASSERT_EQ(SORT(List, TypeUpper), Expected);
    };
}
