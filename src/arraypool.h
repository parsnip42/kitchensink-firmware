#ifndef INCLUDED_ARRAYPOOL_H
#define INCLUDED_ARRAYPOOL_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <initializer_list>

template <typename Pool, typename Index>
class ArrayPool
{
public:
    constexpr ArrayPool()
        : mPoolSize(0)
    { }

public:
    constexpr std::size_t size() const
    {
        return mIndex.size();
    }

    constexpr std::size_t poolSize() const
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
            entry.begin = mPool.begin() + newBegin;
            entry.end = mPool.begin() + newEnd;
        }
        else
        {
            auto point(entry.end);

            for (auto& entry : mIndex)
            {
                entry.shift(point, shift);
            }
            
            shiftPool(point, shift);

            std::copy(begin, end, entry.begin);
            entry.end += shift;
        }
    }

private:
    void shiftPool(typename Pool::iterator point, int32_t shift)
    {
        if (shift < 0)
        {
            std::move(point,
                      mPool.begin() + mPoolSize,
                      point + shift);
        }
        else
        {
            std::move_backward(point,
                               mPool.begin() + mPoolSize,
                               mPool.begin() + mPoolSize + shift);
        }

        mPoolSize += shift;
    }
    
private:
    Pool        mPool;
    Index       mIndex;
    std::size_t mPoolSize;

public:
    typedef typename Pool::const_iterator         const_iterator;
    typedef typename Pool::const_reverse_iterator const_reverse_iterator;
    typedef typename Index::value_type            Entry;
    
    constexpr const_iterator begin() const
    {
        return mPool.begin();
    }

    constexpr const_iterator end() const
    {
        return mPool.end();
    }
    
    constexpr const_reverse_iterator rbegin() const
    {
        return mPool.rbegin();
    }

    constexpr const_reverse_iterator rend() const
    {
        return mPool.rend();
    }

    constexpr const Entry& operator[](int index) const
    {
        return mIndex[index];
    }

    Entry& operator[](int index)
    {
        return mIndex[index];
    }
};

#endif
