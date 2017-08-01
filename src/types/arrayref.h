#ifndef INCLUDED_ARRAYREF_H
#define INCLUDED_ARRAYREF_H

#include "types/range.h"

#include <cstdint>

template <typename Iterator>
class ArrayRef
{
public:
    typedef Iterator iterator;
    
public:
    template <typename Array>
    explicit ArrayRef(Array& array);

    ArrayRef(iterator begin,
             iterator end);

public:
    typename Iterator::reference operator[](std::size_t index);
    std::size_t size() const;
    ArrayRef subset(std::size_t start) const;
    ArrayRef subset(std::size_t start, std::size_t len) const;

private:
    Range<Iterator> mRange;
};


template <typename Iterator>
template <typename Array>
inline
ArrayRef<Iterator>::ArrayRef(Array& array)
    : mRange(array.begin(), array.end())
{ }

template <typename Iterator>
inline
ArrayRef<Iterator>::ArrayRef(iterator begin,
                             iterator end)
    : mRange(begin, end)
{ }

template <typename Iterator>
inline
typename Iterator::reference ArrayRef<Iterator>::operator[](std::size_t index)
{
    return *(mRange.begin() + index);
}

template <typename Iterator>
inline
std::size_t ArrayRef<Iterator>::size() const
{
    return std::distance(mRange.begin(), mRange.end());
}

template <typename Iterator>
inline
ArrayRef<Iterator> ArrayRef<Iterator>::subset(std::size_t start) const
{
    return ArrayRef<Iterator>(
        (start < size()) ? (mRange.begin() + start) : mRange.end(),
        mRange.end());
}

template <typename Iterator>
inline
ArrayRef<Iterator> ArrayRef<Iterator>::subset(std::size_t start, std::size_t len) const
{
    return ArrayRef<Iterator>(
        (start < size()) ? (mRange.begin() + start) : mRange.end(),
        (start + len) < size() ? (mRange.begin() + start + len) : mRange.end());
}

#endif
