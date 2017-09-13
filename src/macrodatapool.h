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
    MacroDataPool();

public:
    void clear();
    
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
void MacroDataPool::clear()
{
    pool.clear();
}

#endif
