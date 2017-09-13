#ifndef INCLUDED_MACRODATAPOOL_H
#define INCLUDED_MACRODATAPOOL_H

#include "event/event.h"
#include "types/arraypool.h"
#include "config.h"

#include <array>

class MacroDataPool
{
private:
    typedef ArrayPool<Event> Pool;

public:
    typedef Pool::const_iterator const_iterator;
    typedef Pool::Content        Content;
    
public:
    MacroDataPool();

public:
    std::size_t size() const;

public:
    bool insert(int index, Pool::const_iterator begin, Pool::const_iterator end);
    Pool::Content operator[](int index) const;
    
private:
    std::array<Event, Config::kMacroPoolSize>      poolData;
    std::array<Range<Event*>, Config::kMacroCount> indexData;
    Pool mArrayPool;
};


inline
MacroDataPool::MacroDataPool()
    : mArrayPool(indexData.begin(), indexData.end(),
                 poolData.begin(),  poolData.end())
{ }

inline
std::size_t MacroDataPool::size() const
{
    return mArrayPool.size();
}

inline
bool MacroDataPool::insert(int index, Pool::const_iterator begin, Pool::const_iterator end)
{
    return mArrayPool.insert(index, begin, end);
}

inline
MacroDataPool::Content MacroDataPool::operator[](int index) const
{
    return mArrayPool[index];
}

#endif
