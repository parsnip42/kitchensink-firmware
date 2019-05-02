#include "gtest/gtest.h"
#include <cstring>

#include "types/arraypool.h"

TEST(ArrayPool, Empty)
{
    ArrayPool<int> ap(0, 0, 0, 0);

    ASSERT_EQ(ap.usage(), 0);
    ASSERT_EQ(ap.capacity(), 0);

    ASSERT_FALSE(ap.insert(0, 0, 0));

    int test[] = { 0, 1, 2 };
    
    ASSERT_FALSE(ap.insert(0, test, test + 3));
}

TEST(ArrayPool, Simple)
{
    Range<int*> index[3];
    int data[12];

    ArrayPool<int> ap(index, index + 3, data, data + 12);

    ASSERT_EQ(ap.usage(), 0);
    ASSERT_EQ(ap.capacity(), 12);

    int testA[] = { 0, 1, 2 };
    ASSERT_TRUE(ap.insert(1, testA, testA + 3));

    ASSERT_EQ(ap.usage(), 3);
    ASSERT_EQ(ap.capacity(), 12);

    int testB[] = { 3, 4, 5, 6, 7, 8, 9 };
    ASSERT_TRUE(ap.insert(2, testB, testB + 7));

    ASSERT_FALSE(ap.insert(3, 0, 0));
    ASSERT_FALSE(ap.insert(3, testA, testA + 3));
    ASSERT_FALSE(ap.insert(0, testA, testA + 3));

    ASSERT_EQ(ap.usage(), 10);
    ASSERT_EQ(ap.capacity(), 12);

    int testC[] = { 10, 11 };
    ASSERT_TRUE(ap.insert(0, testC, testC + 2));

    ASSERT_EQ(ap.usage(), 12);
    ASSERT_EQ(ap.capacity(), 12);

    {
        auto contentC(ap[0]);
    
        ASSERT_TRUE(std::memcmp(testC, contentC.begin(), 2) == 0);
    
        auto contentA(ap[1]);
    
        ASSERT_TRUE(std::memcmp(testA, contentA.begin(), 3) == 0);

        auto contentB(ap[2]);
    
        ASSERT_TRUE(std::memcmp(testB, contentB.begin(), 7) == 0);
    }

    ASSERT_TRUE(ap.insert(1, 0, 0));
    ASSERT_EQ(ap.usage(), 9);

    {
        auto contentC(ap[0]);
    
        ASSERT_TRUE(std::memcmp(testC, contentC.begin(), 2) == 0);
    
        ASSERT_EQ(ap[1].begin(), ap[1].end());

        auto contentB(ap[2]);
    
        ASSERT_TRUE(std::memcmp(testB, contentB.begin(), 7) == 0);
    }
    
    ap.clear();
    
    ASSERT_EQ(ap.usage(), 0);
    ASSERT_EQ(ap.capacity(), 12);

    ASSERT_EQ(ap[0].begin(), ap[0].end());
    ASSERT_EQ(ap[1].begin(), ap[1].end());
    ASSERT_EQ(ap[2].begin(), ap[2].end());
}
