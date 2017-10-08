#ifndef INCLUDED_DATAREF_H
#define INCLUDED_DATAREF_H

#include "types/range.h"
#include "types/strref.h"

#include <array>
#include <cstdint>

class DataRef
{
public:
    typedef const uint8_t* const_iterator;

public:
    constexpr DataRef();
    
    DataRef(const StrRef& str);
    
    DataRef(const char* str);
    
    constexpr DataRef(uint8_t octet);

    constexpr DataRef(const_iterator begin,
                      const_iterator end);

    template <std::size_t Capacity>
    constexpr DataRef(const std::array<uint8_t, Capacity>& array);

public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;
    constexpr std::size_t size() const;
    constexpr uint8_t operator[](std::size_t index) const;
    
private:
    Range<const_iterator> mRange;
    uint8_t               mInPlace;

private:
    friend bool operator==(const DataRef& lhs, const DataRef& rhs);
};

bool operator==(const DataRef& lhs, const DataRef& rhs);
bool operator!=(const DataRef& lhs, const DataRef& rhs);


inline
constexpr DataRef::DataRef()
    : mRange(nullptr, nullptr)
    , mInPlace(0)
{ }

inline
DataRef::DataRef(const StrRef& str)
    : mRange(reinterpret_cast<const_iterator>(str.begin()),
             reinterpret_cast<const_iterator>(str.end()))
    , mInPlace(0)
{ }

inline
DataRef::DataRef(const char* str)
    : DataRef(StrRef(str))
{ }

inline
constexpr DataRef::DataRef(uint8_t octet)
    : mRange(&mInPlace, &mInPlace + 1)
    , mInPlace(octet)
{ }

inline
constexpr DataRef::DataRef(const_iterator begin,
                           const_iterator end)
    : mRange(begin, end)
    , mInPlace(0)
{ }

template <std::size_t Capacity>
inline
constexpr DataRef::DataRef(const std::array<uint8_t, Capacity>& array)
    : mRange(array.begin(), array.end())
{ }

inline
constexpr DataRef::const_iterator DataRef::begin() const
{
    return mRange.begin();
}

inline
constexpr DataRef::const_iterator DataRef::end() const
{
    return mRange.end();
}

inline
constexpr std::size_t DataRef::size() const
{
    return mRange.end() - mRange.begin();
}

inline
constexpr uint8_t DataRef::operator[](std::size_t index) const
{
    return *(mRange.begin() + index);
}


inline
bool operator==(const DataRef& lhs, const DataRef& rhs)
{
    return (lhs.size() == rhs.size()) &&
        std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

inline
bool operator!=(const DataRef& lhs, const DataRef& rhs)
{
    return !(lhs == rhs);
}

#endif
