#ifndef INCLUDED_CIRCULARBUFFER_H
#define INCLUDED_CIRCULARBUFFER_H

#include <array>
#include <algorithm>
#include <cstdint>

#include "types/circularbufferiterator.h"

template <typename T, std::size_t Capacity>
class CircularBuffer
{
private:
    typedef std::array<T, Capacity> Data;

public:
    typedef CircularBufferIterator<T, Capacity> iterator;
    
public:
    constexpr CircularBuffer();

public:
    constexpr std::size_t size() const;
    constexpr bool full() const;
    constexpr bool empty() const;
    void pushBack(const T& value);
    void pushFront(const T& value);
    void insert(iterator position, const T& value);
    const T& peek() const;
    T pop();

public:
    iterator begin();
    iterator end();
    
private:
    Data        mData;
    std::size_t mStart;
    std::size_t mEnd;
    bool        mFull;
};

template <typename T, std::size_t Capacity>
inline
constexpr CircularBuffer<T, Capacity>::CircularBuffer()
    : mStart(0)
    , mEnd(0)
    , mFull(false)
{ }

template <typename T, std::size_t Capacity>
inline
void CircularBuffer<T, Capacity>::pushBack(const T& value)
{
    mData[mEnd] = value;
    mEnd = (mEnd + 1) % Capacity;
    
    mFull = (mStart == mEnd);
}

template <typename T, std::size_t Capacity>
inline
void CircularBuffer<T, Capacity>::pushFront(const T& value)
{
    mStart = (mStart + Capacity - 1) % Capacity;
    mData[mStart] = value;

    mFull = (mStart == mEnd);
}

template <typename T, std::size_t Capacity>
inline
void CircularBuffer<T, Capacity>::insert(typename CircularBuffer<T, Capacity>::iterator position,
                                         const T&                                       value)
{
    auto endRange(end());
    
    mEnd = (mEnd + 1) % Capacity;
    mFull = (mStart == mEnd);

    std::move_backward(position, endRange, end());

    *position = value;
}

template <typename T, std::size_t Capacity>
inline
T CircularBuffer<T, Capacity>::pop()
{
    T value(mData[mStart]);

    mStart = (mStart + 1) % Capacity;
    mFull = false;
    
    return value;
}
template <typename T, std::size_t Capacity>
inline
const T& CircularBuffer<T, Capacity>::peek() const
{
    return mData[mStart];
}

template <typename T, std::size_t Capacity>
inline
constexpr bool CircularBuffer<T, Capacity>::full() const
{
    return mFull;
}

template <typename T, std::size_t Capacity>
inline
constexpr bool CircularBuffer<T, Capacity>::empty() const
{
    return !mFull && (mStart == mEnd);   
}

template <typename T, std::size_t Capacity>
inline
constexpr std::size_t CircularBuffer<T, Capacity>::size() const
{
    return mFull ?
        Capacity :
        ((mStart <= mEnd) ?
            (mEnd - mStart) :
            ((Capacity - mStart) + mEnd));
}

template <typename T, std::size_t Capacity>
inline
typename CircularBuffer<T, Capacity>::iterator CircularBuffer<T, Capacity>::begin()
{
    return iterator(&mData, mStart);
}

template <typename T, std::size_t Capacity>
inline
typename CircularBuffer<T, Capacity>::iterator CircularBuffer<T, Capacity>::end()
{
    return iterator(&mData, mEnd);
}

#endif
