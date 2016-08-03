#ifndef H95E6A20D_63A5_4915_B14F_CD5A080E9728
#define H95E6A20D_63A5_4915_B14F_CD5A080E9728

#include <tlp/base/algo/Value.h>
#include <tlp/base/algo/Valid.h>
#include <tlp/bool/algo/IsEqual.h>

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

#endif
