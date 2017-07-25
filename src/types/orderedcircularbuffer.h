#ifndef INCLUDED_ORDEREDCIRCULARBUFFER_H
#define INCLUDED_ORDEREDCIRCULARBUFFER_H

#include "types/circularbuffer.h"
#include "types/kvpair.h"

#include <algorithm>
#include <cstdint>

template <typename Key, typename Value, std::size_t Capacity>
class OrderedCircularBuffer
{
public:
    typedef KVPair<Key, Value> value_type;
    
public:
    constexpr OrderedCircularBuffer() = default;

public:
    auto peek() const;
    auto pop();

    bool empty() const;
    bool insert(const Key& key, const Value& value);
    bool insert(Key&& key, Value&& value);

private:
    CircularBuffer<value_type, Capacity> mBuffer;
};


template <typename Key, typename Value, std::size_t Capacity>
inline
bool OrderedCircularBuffer<Key, Value, Capacity>::empty() const
{
    return mBuffer.empty();
}

template <typename Key, typename Value, std::size_t Capacity>
inline
bool OrderedCircularBuffer<Key, Value, Capacity>::insert(const Key&   key,
                                                         const Value& value)
{
    if (!mBuffer.full())
    {
        mBuffer.pushBack(value_type(key, value));
        // std::sort(mBuffer.begin(), mBuffer.end());
        
        return true;
    }
    
    return false;
}

template <typename Key, typename Value, std::size_t Capacity>
inline
bool OrderedCircularBuffer<Key, Value, Capacity>::insert(Key&&   key,
                                                         Value&& value)
{
    if (!mBuffer.full())
    {
        mBuffer.pushBack(value_type(key, value));
        // std::sort(mBuffer.begin(), mBuffer.end());
        
        return true;
    }
    
    return false;
}

template <typename Key, typename Value, std::size_t Capacity>
inline
auto OrderedCircularBuffer<Key, Value, Capacity>::peek() const
{
    return mBuffer.peek();
}

template <typename Key, typename Value, std::size_t Capacity>
inline
auto OrderedCircularBuffer<Key, Value, Capacity>::pop()
{
    return mBuffer.pop();
}

#endif /* INCLUDED_ORDEREDCIRCULARBUFFER_H */
