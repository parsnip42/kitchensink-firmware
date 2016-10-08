#include "gtest/gtest.h"

#include "circularbuffer.h"

TEST(CircularBuffer, Default)
{
    CircularBuffer<int, 5> cb;

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, SimplePushPop)
{
    CircularBuffer<int, 5> cb;

    cb.push(123);
    
    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 1);
    ASSERT_EQ(cb.pop(), 123);
    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);    
}

TEST(CircularBuffer, SimplePushFull)
{
    CircularBuffer<int, 5> cb;

    cb.push(0);
    cb.push(1);
    cb.push(2);
    cb.push(3);
    cb.push(4);

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

TEST(CircularBuffer, OverlapPushPop)
{
    CircularBuffer<int, 5> cb;

    cb.push(0);
    cb.push(1);
    cb.push(2);
    cb.push(3);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 4);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 3);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);

    cb.push(0);
    cb.push(1);
    cb.push(2);
    cb.push(3);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 4);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);
    ASSERT_EQ(cb.pop(), 3);

    ASSERT_TRUE(cb.empty());
    ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBuffer, OverlapPushFull)
{
    CircularBuffer<int, 5> cb;

    cb.push(0);
    cb.push(1);
    cb.push(2);

    ASSERT_FALSE(cb.empty());
    ASSERT_EQ(cb.size(), 3);

    ASSERT_EQ(cb.pop(), 0);
    ASSERT_EQ(cb.pop(), 1);
    ASSERT_EQ(cb.pop(), 2);

    cb.push(0);
    cb.push(1);
    cb.push(2);
    cb.push(3);
    cb.push(4);

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
