#ifndef INCLUDED_POOLINDEXENTRY_H
#define INCLUDED_POOLINDEXENTRY_H

#include <cstdint>

class PoolIndexEntry
{
public:
    constexpr PoolIndexEntry();
    
    constexpr PoolIndexEntry(std::size_t nBegin,
                             std::size_t nEnd);

public:
    constexpr bool empty() const;
        
public:
    std::size_t begin;
    std::size_t end;
};


inline
constexpr PoolIndexEntry::PoolIndexEntry()
    : begin(0)
    , end(0)
{ }

inline
constexpr PoolIndexEntry::PoolIndexEntry(std::size_t nBegin,
                                         std::size_t nEnd)
    : begin(nBegin)
    , end(nEnd)
{ }

inline
constexpr bool PoolIndexEntry::empty() const
{
    return (begin == end);
}

#endif
