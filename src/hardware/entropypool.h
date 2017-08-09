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
    EntropyPool() = default;

public:
    void insert(uint8_t value);
    std::size_t size() const;

    const_iterator begin() const;
    const_iterator end() const;
    
private:
    Data mData;
    int  mCount;
};


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
