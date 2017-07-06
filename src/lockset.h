#ifndef INCLUDED_LOCKSET_H
#define INCLUDED_LOCKSET_H

#include "lock.h"

#include <array>
#include <cstdint>

class LockSet
{
private:
    typedef std::array<Lock, 30> Data;

public:
    typedef Data::iterator iterator;

public:
    LockSet();

public:
    iterator begin();
    iterator end();
    std::size_t size() const;
    
public:
    const Lock& operator[](std::size_t index) const;
    Lock& operator[](std::size_t index);
    
private:
    Data mData;
};


inline
const Lock& LockSet::operator[](std::size_t index) const
{
    return mData[index];
}

inline
Lock& LockSet::operator[](std::size_t index)
{
    return mData[index];
}

inline
std::size_t LockSet::size() const
{
    return mData.size();
}

inline
LockSet::iterator LockSet::begin()
{
    return mData.begin();
}

inline
LockSet::iterator LockSet::end()
{
    return mData.end();
}

#endif
