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
    constexpr std::size_t size() const;

public:
    bool insert(int index, const_iterator begin, const_iterator end);

    Content operator[](int index) const;
    
private:
    IndexData   mIndexData;
    PoolData    mPoolData;
    std::size_t mPoolSize;
    std::size_t mPoolCapacity;
};


template <typename Element>
inline
ArrayPool<Element>::ArrayPool(IndexElement* indexBegin,
                              IndexElement* indexEnd,
                              Element*      dataBegin,
                              Element*      dataEnd)
    : mIndexData(indexBegin, indexEnd)
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
constexpr std::size_t ArrayPool<Element>::size() const
{
    return std::distance(mIndexData.begin(), mIndexData.end());
}

template <typename Element>
inline
bool ArrayPool<Element>::insert(int index, const_iterator begin, const_iterator end)
{
    auto& entry(*(mIndexData.begin() + index));

    auto entrySize(std::distance(entry.begin(), entry.end()));
    auto dataSize(std::distance(begin, end));

    // Note that if the size of an entry is bigger than the total used size of
    // the pool, then we're already in a complete mess.
    if (((mPoolSize - entrySize) + dataSize) >= mPoolCapacity)
    {
        return false;
    }
    
    std::move(entry.end(),
              entry.end() + mPoolSize,
              entry.begin());

    mPoolSize -= entrySize;

    for (auto& e : mIndexData)
    {
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
typename ArrayPool<Element>::Content ArrayPool<Element>::operator[](int index) const
{
    const auto& entry(*(mIndexData.begin() + index));

    return Content(entry.begin(), entry.end());
}

#endif
