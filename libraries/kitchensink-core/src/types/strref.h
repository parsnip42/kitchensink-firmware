#ifndef INCLUDED_STRREF_H
#define INCLUDED_STRREF_H

#include "range.h"

#include <cstdint>

class StrRef
{
public:
    typedef const char* const_iterator;

public:
    constexpr StrRef(const char* str = "");
    constexpr StrRef(const_iterator begin,
                     const_iterator end);
    
public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;
    constexpr std::size_t length() const;
    constexpr bool empty() const;
    constexpr StrRef substr(std::size_t start) const;
    constexpr StrRef substr(std::size_t start, std::size_t len) const;

public:
    bool equalsCase(const StrRef& str) const;
    bool beginsWith(const StrRef& str) const;
    bool endsWith(const StrRef& str) const;
    bool beginsWithCase(const StrRef& str) const;
    bool endsWithCase(const StrRef& str) const;
    StrRef trim() const;
        
public:
    constexpr const char& operator[](std::size_t n) const;
    
private:
    Range<const_iterator> mRange;

private:
    static constexpr std::size_t termLen(const char* data);
    
private:
    friend bool operator==(const StrRef& lhs, const StrRef& rhs);
};

bool operator==(const StrRef& lhs, const StrRef& rhs);
bool operator!=(const StrRef& lhs, const StrRef& rhs);


inline
constexpr StrRef::StrRef(const char* str)
    : mRange(str, str + termLen(str))
{ }

inline
constexpr StrRef::StrRef(const_iterator begin,
                         const_iterator end)
    : mRange(begin, end)
{ }

inline
constexpr StrRef::const_iterator StrRef::begin() const
{
    return mRange.begin();
}

inline
constexpr StrRef::const_iterator StrRef::end() const
{
    return mRange.end();
}

inline
constexpr std::size_t StrRef::length() const
{
    return mRange.end() - mRange.begin();
}

inline
constexpr bool StrRef::empty() const
{
    return mRange.begin() == mRange.end();
}

inline
constexpr StrRef StrRef::substr(std::size_t start) const
{
    return StrRef(
        (start < length()) ? (mRange.begin() + start) : mRange.end(),
        mRange.end());
}

inline
constexpr StrRef StrRef::substr(std::size_t start, std::size_t len) const
{
    return StrRef(
        (start < length()) ? (mRange.begin() + start) : mRange.end(),
        (start + len) < length() ? (mRange.begin() + start + len) : mRange.end());
}

inline
constexpr const char& StrRef::operator[](std::size_t n) const
{
    return mRange.begin()[n];
}

inline
constexpr std::size_t StrRef::termLen(const char* data)
{
    return (data[0] == '\0') ? 0 : (termLen(data + 1) + 1);
}

inline
bool operator==(const StrRef& lhs, const StrRef& rhs)
{
    return (lhs.length() == rhs.length()) &&
        std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

inline
bool operator!=(const StrRef& lhs, const StrRef& rhs)
{
    return !(lhs == rhs);
}

#endif






