#ifndef INCLUDED_ARRAYREF_H
#define INCLUDED_ARRAYREF_H

#include "types/range.h"

#include <cstdint>

template <typename Array>
class ArrayRef
{
public:
    typedef typename Array::reference reference;
    
public:
    explicit ArrayRef(Array& array);

private:
    ArrayRef(Array&      array,
             std::size_t begin,
             std::size_t end);
    
public:
    reference operator[](std::size_t index) const;
    std::size_t size() const;
    ArrayRef subset(std::size_t start) const;
    ArrayRef subset(std::size_t start, std::size_t len) const;

private:
    Array&      mArray;
    std::size_t mBegin;
    std::size_t mEnd;
};


template <typename Array>
inline
ArrayRef<Array>::ArrayRef(Array& array)
    : mArray(array)
    , mBegin(0)
    , mEnd(array.size())
{ }

template <typename Array>
inline
ArrayRef<Array>::ArrayRef(Array&      array,
                          std::size_t begin,
                          std::size_t end)
    : mArray(array)
    , mBegin(begin)
    , mEnd(end)
{ }

template <typename Array>
inline
typename ArrayRef<Array>::reference ArrayRef<Array>::operator[](std::size_t index) const
{
    return mArray[mBegin + index];
}

template <typename Array>
inline
std::size_t ArrayRef<Array>::size() const
{
    return mEnd - mBegin;
}

template <typename Array>
inline
ArrayRef<Array> ArrayRef<Array>::subset(std::size_t start) const
{
    start += mBegin;
    
    return ArrayRef<Array>(mArray,
                           (start < mEnd) ? start : mEnd,
                           mEnd);
}

template <typename Array>
inline
ArrayRef<Array> ArrayRef<Array>::subset(std::size_t start, std::size_t len) const
{
    start += mBegin;

    return ArrayRef<Array>(mArray,
                           (start < mEnd) ? start : mEnd,
                           (start + len) < mEnd ? (start + len) : mEnd);
}

#endif
