#ifndef INCLUDED_MACRODATAPOOL_H
#define INCLUDED_MACRODATAPOOL_H

#include "event/event.h"
#include "types/arraypool.h"

#include <array>
#include <cstdint>

template <std::size_t Size, std::size_t PoolSize>
class MacroDataPool
{
public:
    typedef ArrayPool<Event> Pool;

public:
    MacroDataPool();

public:
    void clear();

private:
    std::array<Range<Event*>, Size> indexData;
    std::array<Event, PoolSize>     poolData;

public:
    Pool pool;
};


template <std::size_t Size, std::size_t PoolSize>
inline
MacroDataPool<Size, PoolSize>::MacroDataPool()
    : pool(indexData.begin(), indexData.end(),
           poolData.begin(),  poolData.end())
{ }

template <std::size_t Size, std::size_t PoolSize>
inline
void MacroDataPool<Size, PoolSize>::clear()
{
    pool.clear();
}

#endif
