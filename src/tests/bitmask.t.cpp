#include "gtest/gtest.h"

#include "bitmask.h"

TEST(Bitmask, Default)
{
    Bitmask<5> b;

    ASSERT_TRUE(b.empty());
    ASSERT_FALSE(b[0]);
    ASSERT_FALSE(b[1]);
    ASSERT_FALSE(b[2]);
    ASSERT_FALSE(b[3]);
    ASSERT_FALSE(b[4]);
}

TEST(Bitmask, SimpleSetClear)
{
    Bitmask<5> b;

    b[2] = true;

    ASSERT_FALSE(b.empty());
    ASSERT_FALSE(b[0]);
    ASSERT_FALSE(b[1]);
    ASSERT_TRUE(b[2]);
    ASSERT_FALSE(b[3]);
    ASSERT_FALSE(b[4]);

    b[2] = false;

    ASSERT_TRUE(b.empty());
}
