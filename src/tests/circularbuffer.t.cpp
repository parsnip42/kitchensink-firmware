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

TEST(CircularBuffer, Erase)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);

    auto it(cb.begin());

    ++it;
    ++it;

    cb.erase(it);

    std::vector<int> values({ 0, 1, 3 });

    ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                           values.begin()));
}

TEST(CircularBuffer, EraseOverflow)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(9);
    cb.pushBack(9);
    cb.pushBack(9);

    cb.pop();
    cb.pop();
    cb.pop();

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);
    cb.pushBack(3);

    auto it(cb.begin());

    ++it;

    cb.erase(it);
    cb.erase(it);

    std::vector<int> values({ 0, 3 });

    ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                           values.begin()));
}

TEST(CircularBuffer, EraseFirst)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);

    {
        cb.erase(cb.begin());

        std::vector<int> values({ 1, 2 });

        ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                               values.begin()));
    }

    {
        cb.erase(cb.begin());

        std::vector<int> values({ 2 });

        ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                               values.begin()));
    }

    {
        cb.erase(cb.begin());
        ASSERT_TRUE(cb.empty());
    }

}

TEST(CircularBuffer, EraseLast)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(2);


    {
        auto it(cb.end());
        
        --it;
    
        cb.erase(it);
        
        std::vector<int> values({ 0, 1 });
        
        ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                               values.begin()));
    }

    {
        auto it(cb.end());
        
        --it;
    
        cb.erase(it);
        
        std::vector<int> values({ 0 });
        
        ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                               values.begin()));
    }


    {
        auto it(cb.end());
        
        --it;
    
        cb.erase(it);
        ASSERT_TRUE(cb.empty());
    }

}

TEST(CircularBuffer, Insert)
{
    CircularBuffer<int, 5> cb;

    cb.pushBack(0);
    cb.pushBack(1);
    cb.pushBack(3);

    auto it(cb.begin());

    ++it;
    ++it;

    cb.insert(it, 2);

    std::vector<int> values({ 0, 1, 2, 3 });

    ASSERT_TRUE(std::equal(cb.begin(), cb.end(),
                           values.begin()));
}
