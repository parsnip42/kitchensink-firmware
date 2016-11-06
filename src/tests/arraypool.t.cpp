#include "gtest/gtest.h"

#include "arraypool.h"
#include "keyevent.h"
TEST(ArrayPool, Default)
{
    ArrayPool<int, 10, 1024> p;

    ASSERT_EQ(p.poolSize(), 0);
}

TEST(ArrayPool, Insert)
{
    ArrayPool<int, 10, 1024> p;

    int nums[] = {1,2,3};
    
    p.insert(0, nums, nums + 3);

    ASSERT_EQ(p.poolSize(), 3);

    auto entry(p[0]);

    auto it(entry.first);
    
    ASSERT_EQ(*it++, 1);
    ASSERT_EQ(*it++, 2);
    ASSERT_EQ(*it++, 3);

    ASSERT_EQ(it, entry.second);
}

TEST(ArrayPool, Overwrite)
{
    ArrayPool<int, 10, 1024> p;

    {
        int nums[] = {1,2,3};
    
        p.insert(0, nums, nums + 3);

        ASSERT_EQ(p.poolSize(), 3);

        auto entry(p[0]);

        auto it(entry.first);
    
        ASSERT_EQ(*it++, 1);
        ASSERT_EQ(*it++, 2);
        ASSERT_EQ(*it++, 3);

        ASSERT_EQ(it, entry.second);
    }

    {
        int nums[] = {11, 12, 13, 14, 15};
    
        p.insert(0, nums, nums + 5);

        ASSERT_EQ(p.poolSize(), 5);

        auto entry(p[0]);

        auto it(entry.first);
    
        ASSERT_EQ(*it++, 11);
        ASSERT_EQ(*it++, 12);
        ASSERT_EQ(*it++, 13);
        ASSERT_EQ(*it++, 14);
        ASSERT_EQ(*it++, 15);

        ASSERT_EQ(it, entry.second);
    }
    
    {
        int nums[] = {21, 22};
    
        p.insert(0, nums, nums + 2);

        ASSERT_EQ(p.poolSize(), 2);

        auto entry(p[0]);

        auto it(entry.first);
    
        ASSERT_EQ(*it++, 21);
        ASSERT_EQ(*it++, 22);

        ASSERT_EQ(it, entry.second);
    }
}
