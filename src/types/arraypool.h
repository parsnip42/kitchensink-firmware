#ifndef INCLUDED_ARRAYPOOL_H
#define INCLUDED_ARRAYPOOL_H

#include "types/range.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <initializer_list>

template <typename Pool, std::size_t IndexSize>
class ArrayPool
{
public:
    typedef typename Pool::const_iterator         const_iterator;
    typedef typename Pool::const_reverse_iterator const_reverse_iterator;
    typedef Range<const_iterator>                 Content;
    
public:
    ArrayPool();

public:
    constexpr std::size_t size() const;

public:
    bool insert(int index, const std::initializer_list<typename Pool::value_type>& list);

    template <typename Iterator>
    bool insert(int index, Iterator begin, Iterator end);

    Content operator[](int index) const;
    
private:
    typedef std::array<Range<typename Pool::iterator>, IndexSize> Index;
    
    Pool        mPool;
    Index       mIndex;
    std::size_t mPoolSize;
};


template <typename Pool, std::size_t IndexSize>
inline
ArrayPool<Pool, IndexSize>::ArrayPool()
    : mIndex()
    , mPoolSize(10)
{
    for (auto& e : mIndex)
    {
        e.begin = mPool.begin();
        e.end = mPool.begin();
    }
}

template <typename Pool, std::size_t IndexSize>
inline
constexpr std::size_t ArrayPool<Pool, IndexSize>::size() const
{
    return mIndex.size();
}

template <typename Pool, std::size_t IndexSize>
inline
bool ArrayPool<Pool, IndexSize>::insert(int index, const std::initializer_list<typename Pool::value_type>& list)
{
    return insert(index, list.begin(), list.end());
}

template <typename Pool, std::size_t IndexSize>
template <typename Iterator>
inline
bool ArrayPool<Pool, IndexSize>::insert(int index, Iterator begin, Iterator end)
{
    auto& entry(mIndex[index]);

    auto entrySize(std::distance(entry.begin, entry.end));
    auto dataSize(std::distance(begin, end));

    // Note that if the size of an entry is bigger than the total used size of
    // the pool, then we're already in a complete mess.
    if (((mPoolSize - entrySize) + dataSize) >= mPool.size())
    {
        return false;
    }
    
    std::move(entry.end,
              entry.end + mPoolSize,
              entry.begin);

    mPoolSize -= entrySize;

    for (auto& e : mIndex)
    {
        if (e.begin >= entry.end)
        {
            e.begin -= entrySize;
            e.end -= entrySize;
        }
    }
        
    std::copy(begin,
              end,
              mPool.begin() + mPoolSize);

    entry.begin = mPool.begin() + mPoolSize;
        
    mPoolSize += dataSize;

    entry.end = mPool.begin() + mPoolSize;

    return true;
}

template <typename Pool, std::size_t IndexSize>
inline
typename ArrayPool<Pool, IndexSize>::Content ArrayPool<Pool, IndexSize>::operator[](int index) const
{
    const auto& entry(mIndex[index]);
    
    return Range<const_iterator>(entry.begin, entry.end);
}

#endif
