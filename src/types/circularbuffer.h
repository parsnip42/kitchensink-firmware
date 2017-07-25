#ifndef INCLUDED_CIRCULARBUFFER_H
#define INCLUDED_CIRCULARBUFFER_H

#include <array>
#include <cstdint>
#include <iterator>

template <typename T, std::size_t Capacity>
class CircularBuffer
{
private:
    typedef std::array<T, Capacity> Data;

public:
    class iterator
    {
    public:
        typedef T                         value_type;
        typedef T&                        reference_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef std::size_t               distance_type;
        
    private:
        iterator(Data&       data,
                 std::size_t index)
            : mData(data)
            , mIndex(index)
        { }
        
    public:
        reference_type operator*()
        {
            return mData[mIndex];
        }
        
        void operator++(int)
        {
            mIndex = ++mIndex % Capacity;
        };
        
        iterator operator++()
        {
            auto prev(*this);

            ++(*this);

            return prev;
        };

        bool operator==(const iterator& rhs)
        {
            return mIndex == rhs.mIndex;
        };
        
        bool operator!=(const iterator& rhs)
        {
            return mIndex != rhs.mIndex;
        };

    private:
        Data&       mData;
        std::size_t mIndex;

    private:
        friend class CircularBuffer;
    };
    
public:
    constexpr CircularBuffer();

public:
    constexpr std::size_t size() const;
    constexpr bool full() const;
    constexpr bool empty() const;
    void pushBack(const T& value);
    void pushFront(const T& value);
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
bool operator==(const typename CircularBuffer<T, Capacity>::iterator& lhs,
                const typename CircularBuffer<T, Capacity>::iterator& rhs)
{
    return lhs.mIndex == rhs.mIndex;
}

template <typename T, std::size_t Capacity>
inline
bool operator!=(const typename CircularBuffer<T, Capacity>::iterator& lhs,
                const typename CircularBuffer<T, Capacity>::iterator& rhs)
{
    return !(*lhs == *rhs);
}


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
    return iterator(mData, mStart);
}

template <typename T, std::size_t Capacity>
inline
typename CircularBuffer<T, Capacity>::iterator CircularBuffer<T, Capacity>::end()
{
    return iterator(mData, mEnd);
}

#endif
