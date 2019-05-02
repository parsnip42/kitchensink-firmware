#ifndef INCLUDED_ARRAYPOOL_H
#define INCLUDED_ARRAYPOOL_H

#include "types/range.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>

template <typename Element>
class ArrayPool
{
public:
    typedef const Element*        const_iterator;
    typedef Range<const_iterator> Content;
    typedef Range<Element*>       IndexElement;
    
private:
    typedef Range<Element*>      PoolData;
    typedef Range<IndexElement*> IndexData;
    
public:
    ArrayPool(IndexElement* indexBegin,
              IndexElement* indexEnd,
              Element*      dataBegin,
              Element*      dataEnd);

public:
    std::size_t usage() const;
    std::size_t capacity() const;

public:
    bool insert(std::size_t index, const_iterator begin, const_iterator end);
    void clear();
    
    Content operator[](std::size_t index) const;
    
private:
    IndexData   mIndexData;
    std::size_t mIndexCapacity;
    PoolData    mPoolData;
    std::size_t mPoolSize;
    std::size_t mPoolCapacity;

private:
    ArrayPool(const ArrayPool&) = delete;
    ArrayPool& operator=(const ArrayPool&) = delete;
};


template <typename Element>
inline
ArrayPool<Element>::ArrayPool(IndexElement* indexBegin,
                              IndexElement* indexEnd,
                              Element*      dataBegin,
                              Element*      dataEnd)
    : mIndexData(indexBegin, indexEnd)
    , mIndexCapacity(std::distance(indexBegin, indexEnd))
    , mPoolData(dataBegin, dataEnd)
    , mPoolSize(0)
    , mPoolCapacity(std::distance(dataBegin, dataEnd))
{
    for (auto& e : mIndexData)
    {
        e.begin() = mPoolData.begin();
        e.end()   = mPoolData.begin();
    }
}

template <typename Element>
inline
std::size_t ArrayPool<Element>::usage() const
{
    return mPoolSize;
}

template <typename Element>
inline
std::size_t ArrayPool<Element>::capacity() const
{
    return mPoolCapacity;
}

template <typename Element>
inline
bool ArrayPool<Element>::insert(std::size_t index, const_iterator begin, const_iterator end)
{
    if (index >= mIndexCapacity)
    {
        return false;
    }
    
    auto& entry(*(mIndexData.begin() + index));

    auto entrySize(std::distance(entry.begin(), entry.end()));
    auto dataSize(std::distance(begin, end));

    // Note that if the size of an existing entry is bigger than the total used
    // size of the pool, then we're already in a complete mess.
    if (((mPoolSize - entrySize) + dataSize) > mPoolCapacity)
    {
        return false;
    }
    
    std::move(entry.end(),
              entry.end() + mPoolSize,
              entry.begin());

    mPoolSize -= entrySize;

    for (auto& e : mIndexData)
    {
        // Note here that entry.end() corresponds to the element following the
        // end of the entry, so adjacent entries may start at this point.
        if (e.begin() >= entry.end())
        {
            e.begin() -= entrySize;
            e.end() -= entrySize;
        }
    }
    
    std::copy(begin,
              end,
              mPoolData.begin() + mPoolSize);

    entry.begin() = mPoolData.begin() + mPoolSize;
        
    mPoolSize += dataSize;

    entry.end() = mPoolData.begin() + mPoolSize;

    return true;
}

template <typename Element>
inline
void ArrayPool<Element>::clear()
{
    for (auto& e : mIndexData)
    {
        e.begin() = mPoolData.begin();
        e.end()   = mPoolData.begin();
    }

    mPoolSize = 0;
}

template <typename Element>
inline
typename ArrayPool<Element>::Content ArrayPool<Element>::operator[](std::size_t index) const
{
    if (index >= mIndexCapacity)
    {
        return Content(mPoolData.begin(),
                       mPoolData.begin());
    }

    const auto& entry(*(mIndexData.begin() + index));

    return Content(entry.begin(), entry.end());
}

#endif
