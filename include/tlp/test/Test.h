#ifndef H2FBB703F_2DC3_46B1_9587_2A90DA15C335
#define H2FBB703F_2DC3_46B1_9587_2A90DA15C335

#include <tlp/base/algo/Value.h>
#include <tlp/base/algo/Valid.h>
#include <tlp/bool/algo/IsEqual.h>
#include <tlp/utils/UniqueName.h>
#include <iostream>

#define ASSERT_TRUE(T)                  \
static_assert(__value(T), "TLP Error: expect "#T" be true, but be false!")

#define ASSERT_FALSE(T)                 \
static_assert(!(__value(T)), "TLP Error: expect "#T" be false, but be true!")

#define ASSERT_VALID(T)                 \
static_assert(__value(__valid(T)), "TLP Error: expect "#T" be valid, but be invalid!")

#define ASSERT_INVALID(T)               \
static_assert(!(__value(__valid(T))), "TLP Error: expect "#T" be invalid, but be valid!")

#define ASSERT_EQ(T, Expected)          \
static_assert(__value(__is_eq(T, Expected)), "TLP Error: expect "#T" be equal to "#Expected"!")

#define ASSERT_NE(T, Expected)          \
static_assert(!(__value(__is_eq(T, Expected))), "TLP Error: expect "#T" be not equal to "#Expected"!")

#define FIXTURE(Name) namespace Name

#define TEST(Name) struct UNIQUE_NAME(Test_)

#define TLP_RUN_ALL_TESTS()             \
int main() { std::cout << "TLP RUN ALL TESTS OK!!!" << std::endl; return 0; }

#endif
