#ifndef INCLUDED_ENTROPYPOOL_H
#define INCLUDED_ENTROPYPOOL_H

#include "crypto/cryptotypes.h"
#include "config.h"

#include <array>

class EntropyPool
{
private:
    typedef std::array<uint8_t, Config::kEntropyPoolSize> Data;

public:
    typedef Data::const_iterator const_iterator;
    
public:
    EntropyPool();

public:
    bool read(std::array<uint8_t, 32>& output);

public:
    std::size_t size() const;
    std::size_t count() const;
    std::size_t entryCount() const;

    const_iterator begin() const;
    const_iterator end() const;

    void insert(uint8_t value);
    void clear();

private:
    Data        mData;
    std::size_t mCount;

private:
    EntropyPool(const EntropyPool&) = delete;
    EntropyPool& operator=(const EntropyPool&) = delete;
};


inline
EntropyPool::EntropyPool()
    : mCount(0)
{ }

inline
std::size_t EntropyPool::size() const
{
    return mData.size();
}

inline
std::size_t EntropyPool::count() const
{
    return mCount;
}

inline
std::size_t EntropyPool::entryCount() const
{
    return mCount / (32 * Config::kEntropySourceFactor);
}

inline
EntropyPool::const_iterator EntropyPool::begin() const
{
    return mData.begin();
}

inline
EntropyPool::const_iterator EntropyPool::end() const
{
    return mData.begin() + std::min(mCount, mData.size());
}

inline
void EntropyPool::insert(uint8_t value)
{
    mData[mCount % mData.size()] ^= value;
    
    ++mCount;
}

inline
void EntropyPool::clear()
{
    mCount = 0;
}

#endif
