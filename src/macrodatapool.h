#ifndef INCLUDED_MACRODATAPOOL_H
#define INCLUDED_MACRODATAPOOL_H

#include "event/event.h"
#include "types/arraypool.h"
#include "config.h"

#include <array>

class MacroDataPool
{
public:
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

public:
    Pool pool;
};


inline
MacroDataPool::MacroDataPool()
    : pool(indexData.begin(), indexData.end(),
           poolData.begin(),  poolData.end())
{ }

inline
std::size_t MacroDataPool::size() const
{
    return pool.size();
}

inline
bool MacroDataPool::insert(int index, Pool::const_iterator begin, Pool::const_iterator end)
{
    return pool.insert(index, begin, end);
}

inline
MacroDataPool::Content MacroDataPool::operator[](int index) const
{
    return pool[index];
}

#endif
