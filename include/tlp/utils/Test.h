#ifndef H2FBB703F_2DC3_46B1_9587_2A90DA15C335
#define H2FBB703F_2DC3_46B1_9587_2A90DA15C335

#include <tlp/utils/IsEqual.h>
#include <tlp/utils/UniqueName.h>
#include <iostream>

#define ASSERT_TRUE(Value)              \
static_assert((Value), "TLP Error: expect "#Value" be true, but be false!")

#define ASSERT_FALSE(Value)             \
static_assert(!(Value), "TLP Error: expect "#Value" be false, but be true!")

#define ASSERT_EQ(T, Expected)          \
static_assert(TLP_NS::IsEqual<T, Expected>::Value, "TLP Error: expect "#T" be equal to "#Expected"!")

#define ASSERT_NE(T, Expected)          \
static_assert(!(TLP_NS::IsEqual<T, Expected>::Value), "TLP Error: expect "#T" be not equal to "#Expected"!")

#define ASSERT_VALUE_EQ(V, Expected)    \
static_assert((V) == (Expected), "TLP Error: expect "#V" be equal to "#Expected"!")

#define ASSERT_VALUE_NE(V, Expected)    \
static_assert((V != Expected), "TLP Error: expect "#V" be not equal to "#Expected"!")

#define FIXTURE(Name) namespace Name

#define TEST(Name) struct UNIQUE_NAME(Test_)

#define TLP_RUN_ALL_TESTS()             \
int main() { std::cout << "TLP RUN ALL TESTS OK!!!" << std::endl; return 0; }

#endif
