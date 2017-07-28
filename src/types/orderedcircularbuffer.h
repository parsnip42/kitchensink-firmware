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

private:
    typedef CircularBuffer<value_type, Capacity> Buffer;

public:
    typedef typename Buffer::iterator iterator;
    
public:
    constexpr OrderedCircularBuffer() = default;

public:
    auto peek() const;
    auto pop();

    std::size_t size() const;
    bool empty() const;
    auto insert(const value_type& value);
    void erase(iterator position);
    
public:
    iterator begin() { return mBuffer.begin(); }
    iterator end() { return mBuffer.end(); }
    
private:
     Buffer mBuffer;
};


template <typename Key, typename Value, std::size_t Capacity>
inline
std::size_t OrderedCircularBuffer<Key, Value, Capacity>::size() const
{
    return mBuffer.size();
}

template <typename Key, typename Value, std::size_t Capacity>
inline
bool OrderedCircularBuffer<Key, Value, Capacity>::empty() const
{
    return mBuffer.empty();
}

template <typename Key, typename Value, std::size_t Capacity>
inline
auto OrderedCircularBuffer<Key, Value, Capacity>::insert(const value_type& value)
{
    auto position(std::lower_bound(mBuffer.begin(),
                                   mBuffer.end(),
                                   value));
        
    mBuffer.insert(position, value);

    return position;
}

template <typename Key, typename Value, std::size_t Capacity>
inline
void OrderedCircularBuffer<Key, Value, Capacity>::erase(iterator position)
{
    mBuffer.erase(position);
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
