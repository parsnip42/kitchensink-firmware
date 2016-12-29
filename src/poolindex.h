#ifndef INCLUDED_POOLINDEX_H
#define INCLUDED_POOLINDEX_H

#include "poolindexentry.h"

#include <array>
#include <cstdint>

template <typename std::size_t Capacity>
class PoolIndex
{
public:
    static constexpr std::size_t kCapacity = Capacity;

public:
    typedef PoolIndexEntry Entry;
    
private:
    typedef std::array<PoolIndexEntry, Capacity> Index;

public:
    constexpr PoolIndex() = default;

public:
    void shift(uint32_t point, int32_t shift);
    
public:
    const PoolIndexEntry& operator[](int index) const;
    PoolIndexEntry& operator[](int index);

private:
    Index mIndex;
};


template <typename std::size_t Capacity>
inline
void PoolIndex<Capacity>::shift(uint32_t point, int32_t shift)
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

template <typename std::size_t Capacity>
inline
const PoolIndexEntry& PoolIndex<Capacity>::operator[](int index) const
{
    return mIndex[index];
}
    
template <typename std::size_t Capacity>
inline
PoolIndexEntry& PoolIndex<Capacity>::operator[](int index)
{
    return mIndex[index];
}

#endif
