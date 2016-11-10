#ifndef INCLUDED_ARRAYPOOL_H
#define INCLUDED_ARRAYPOOL_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <initializer_list>

template <typename Pool, std::size_t IndexCapacity>
class ArrayPool
{
public:
    constexpr ArrayPool()
        : mPoolSize(0)
    { }

public:
    std::size_t poolSize() const
    {
        return mPoolSize;
    }
    
public:
    void insert(int index, const std::initializer_list<typename Pool::value_type>& list)
    {
        insert(index, list.begin(), list.end());
    }

    template <typename Iterator>
    void insert(int index, Iterator begin, Iterator end)
    {
        auto& entry(mIndex[index]);

        auto currentSize(entry.end - entry.begin);
        auto newSize(std::distance(begin, end));
        auto shift(int32_t(newSize) - int32_t(currentSize));

        if (currentSize == 0)
        {
            auto newBegin(mPoolSize);
            auto newEnd(newBegin + newSize);

            std::copy(begin, end, mPool.begin() + newBegin);
            mPoolSize += newSize;
            entry.begin = newBegin;
            entry.end = newEnd;
        }
        else
        {
            auto point(entry.end);

            shiftIndex(point, shift);
            shiftPool(point, shift);

            std::copy(begin, end, mPool.begin() + entry.begin);
            entry.end += shift;
        }
    }

private:
    void shiftIndex(uint32_t point, int32_t shift)
    {
        for (auto& entry : mIndex)
        {
            if (entry.begin > point)
            {
                entry.begin += shift;
                entry.end += shift;
            }
        }
    }

    void shiftPool(uint32_t point, int32_t shift)
    {
        if (shift < 0)
        {
            std::move(mPool.begin() + point,
                      mPool.begin() + mPoolSize,
                      mPool.begin() + point + shift);
        }
        else
        {
            std::move_backward(mPool.begin() + point,
                               mPool.begin() + mPoolSize,
                               mPool.begin() + mPoolSize + shift);
        }

        mPoolSize += shift;
    }
    
public:
    class Entry
    {
    public:
        Entry()
            : begin(0)
            , end(0)
        { }
        
        Entry(std::size_t nBegin,
              std::size_t nEnd)
            : begin(nBegin)
            , end(nEnd)
        { }

    public:
        bool empty() const
        {
            return (begin == end);
        }
        
    public:
        std::size_t begin;
        std::size_t end;
    };
    
private:
    typedef std::array<Entry, IndexCapacity> Index;
    
    Pool        mPool;
    Index       mIndex;
    std::size_t mPoolSize;

public:
    typedef typename Pool::const_iterator         const_iterator;
    typedef typename Pool::const_reverse_iterator const_reverse_iterator;

    const_iterator begin() const
    {
        return mPool.begin();
    }

    const_iterator end() const
    {
        return mPool.end();
    }
    
    const_reverse_iterator rbegin() const
    {
        return mPool.rbegin();
    }

    const_reverse_iterator rend() const
    {
        return mPool.rend();
    }

    Entry operator[](int index) const
    {
        return mIndex[index];
    }
};

#endif
