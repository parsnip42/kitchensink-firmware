#include "gtest/gtest.h"

#include "types/circularbuffer.h"

#include <algorithm>
#include <vector>

TEST(CircularBuffer, Default)
{
    CircularBuffer<int, 5> cb;

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, SimplePushBackPop)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(123);
    
    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 1);
    ASSERT_EQ(cb.pop(), 123);
    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);    
}

TEST(CircularBuffer, SimplePushBackFull)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);
    cb.pushBack(4);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 5);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 3);
    ASSERT_EQ(cb.pop(), 4);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, OverlapPushBackPop)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 4);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 3);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 4);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 3);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, OverlapPushBackFull)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 3);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);
    cb.pushBack(4);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 5);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 3);
    ASSERT_EQ(cb.pop(), 4);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, SimplePushFrontPop)
{
    CircularBuffer<int, 5> cb;

    cb.pushFront(123);
    
    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 1);
    ASSERT_EQ(cb.pop(), 123);
    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);    
}

TEST(CircularBuffer, SimplePushFrontFull)
{
    CircularBuffer<int, 5> cb;

    cb.pushFront(0);
    cb.pushFront(1);
    cb.pushFront(2);
    cb.pushFront(3);
    cb.pushFront(4);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 5);

    ASSERT_EQ(cb.pop(), 4);
    ASSERT_EQ(cb.pop(), 3);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 0);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, OverlapPushFrontPop)
{
    CircularBuffer<int, 5> cb;

    cb.pushFront(0);
    cb.pushFront(1);
    cb.pushFront(2);
    cb.pushFront(3);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 4);

    ASSERT_EQ(cb.pop(), 3);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 0);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);

    cb.pushFront(0);
    cb.pushFront(1);
    cb.pushFront(2);
    cb.pushFront(3);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 4);

    ASSERT_EQ(cb.pop(), 3);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 0);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, iterate)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);

    std::vector<int> values({ 0, 1, 2, 3 });

    ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                           values.begin()));
}
