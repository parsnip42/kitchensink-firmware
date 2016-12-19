#ifndef INCLUDED_CIRCULARBUFFER_H
#define INCLUDED_CIRCULARBUFFER_H

#include <array>
#include <cstdint>

namespace Types
{

template <typename T, std::size_t Capacity>
class CircularBuffer
{
public:
    constexpr CircularBuffer();

public:
    constexpr std::size_t size() const;
    constexpr bool empty() const;
    void pushBack(const T& value);
    void pushFront(const T& value);
    T pop();
    
private:
    std::size_t             mStart;
    std::size_t             mEnd;
    bool                    mFull;
    std::array<T, Capacity> mData;
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
T CircularBuffer<T, Capacity>::pop()
{
    T value(mData[mStart]);

    mStart = (mStart + 1) % Capacity;
    mFull = false;
    
    return value;
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

}

#endif
