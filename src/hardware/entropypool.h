#ifndef INCLUDED_ENTROPYPOOL_H
#define INCLUDED_ENTROPYPOOL_H

#include <array>

class EntropyPool
{
private:
    typedef std::array<uint8_t, 1024> Data;

public:
    typedef Data::const_iterator const_iterator;
    
public:
    EntropyPool();

public:
    std::array<uint8_t, 32> read();
    
public:
    void insert(uint8_t value);
    std::size_t size() const;
    std::size_t count() const;

    const_iterator begin() const;
    const_iterator end() const;
    
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
void EntropyPool::insert(uint8_t value)
{
    mData[mCount % mData.size()] = value;

    ++mCount;
}

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
EntropyPool::const_iterator EntropyPool::begin() const
{
    return mData.begin();
}

inline
EntropyPool::const_iterator EntropyPool::end() const
{
    return mData.end();
}

#endif
