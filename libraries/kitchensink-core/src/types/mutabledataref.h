#ifndef INCLUDED_MUTABLEDATAREF_H
#define INCLUDED_MUTABLEDATAREF_H

#include "types/range.h"

#include <array>
#include <cstdint>

class MutableDataRef
{
public:
    typedef uint8_t* iterator;

public:
    constexpr MutableDataRef();
    
    constexpr MutableDataRef(iterator begin,
                             iterator end);

    template <std::size_t Capacity>
    constexpr MutableDataRef(std::array<uint8_t, Capacity>& array);

public:
    constexpr iterator begin() const;
    constexpr iterator end() const;
    constexpr std::size_t size() const;
    constexpr uint8_t& operator[](std::size_t index) const;
    MutableDataRef subset(std::size_t start) const;
    MutableDataRef subset(std::size_t start, std::size_t len) const;

private:
    Range<iterator> mRange;

private:
    friend bool operator==(const MutableDataRef& lhs, const MutableDataRef& rhs);
};

bool operator==(const MutableDataRef& lhs, const MutableDataRef& rhs);
bool operator!=(const MutableDataRef& lhs, const MutableDataRef& rhs);


inline
constexpr MutableDataRef::MutableDataRef()
    : mRange(nullptr, nullptr)
{ }

inline
constexpr MutableDataRef::MutableDataRef(iterator begin,
                                         iterator end)
    : mRange(begin, end)
{ }

template <std::size_t Capacity>
inline
constexpr MutableDataRef::MutableDataRef(std::array<uint8_t, Capacity>& array)
    : mRange(array.begin(), array.end())
{ }

inline
constexpr MutableDataRef::iterator MutableDataRef::begin() const
{
    return mRange.begin();
}

inline
constexpr MutableDataRef::iterator MutableDataRef::end() const
{
    return mRange.end();
}

inline
constexpr std::size_t MutableDataRef::size() const
{
    return mRange.end() - mRange.begin();
}

inline
constexpr uint8_t& MutableDataRef::operator[](std::size_t index) const
{
    return *(mRange.begin() + index);
}

inline
MutableDataRef MutableDataRef::subset(std::size_t start) const
{
    if (start >= size())
    {
        return MutableDataRef();
    }
    else
    {
        return MutableDataRef(mRange.begin() + start,
                              mRange.end());
    }
}

inline
MutableDataRef MutableDataRef::subset(std::size_t start, std::size_t len) const
{
    if (start >= size())
    {
        return MutableDataRef();
    }
    else if (len >= (size() - start))
    {
        return MutableDataRef(mRange.begin() + start,
                              mRange.end());
    }
    else
    {
        return MutableDataRef(mRange.begin() + start,
                              mRange.begin() + start + len);
    }
}

inline
bool operator==(const MutableDataRef& lhs, const MutableDataRef& rhs)
{
    return (lhs.size() == rhs.size()) &&
            std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

inline
bool operator!=(const MutableDataRef& lhs, const MutableDataRef& rhs)
{
    return !(lhs == rhs);
}

#endif
