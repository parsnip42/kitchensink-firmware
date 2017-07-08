#ifndef INCLUDED_STRREF_H
#define INCLUDED_STRREF_H

#include <algorithm>
#include <cstdint>
#include <cstring>

namespace StrRefImpl
{

inline
constexpr std::size_t strSize(const char* data)
{
    return (data[0] == '\0') ? 0 : (1 + strSize(data + 1));
}

}

class StrRef
{
public:
    typedef const char* const_iterator;
    
public:
    constexpr StrRef(const char* str = "");
    constexpr StrRef(const char* begin, const char* end);
    
public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;
    constexpr std::size_t size() const;
    constexpr bool empty() const;
    constexpr StrRef substr(std::size_t start) const;
    constexpr StrRef substr(std::size_t start, std::size_t len) const;

public:
    const char& operator[](std::size_t n) const;
    
private:
    const char* mBegin;
    const char* mEnd;

private:
    friend bool operator==(const StrRef& lhs, const StrRef& rhs);
};

bool operator==(const StrRef& lhs, const StrRef& rhs);
bool operator!=(const StrRef& lhs, const StrRef& rhs);


inline
constexpr StrRef::StrRef(const char* str)
    : mBegin(str)
    , mEnd(str + StrRefImpl::strSize(str))
{ }

inline
constexpr StrRef::StrRef(const char* begin, const char* end)
    : mBegin(begin)
    , mEnd(end)
{ }

inline
constexpr StrRef::const_iterator StrRef::begin() const
{
    return mBegin;
}

inline
constexpr StrRef::const_iterator StrRef::end() const
{
    return mEnd;
}

inline
constexpr std::size_t StrRef::size() const
{
    return mEnd - mBegin;
}

inline
constexpr bool StrRef::empty() const
{
    return mBegin == mEnd;
}

inline
constexpr StrRef StrRef::substr(std::size_t start) const
{
    return StrRef((start < size()) ? (mBegin + start) : mEnd, mEnd);
}

inline
constexpr StrRef StrRef::substr(std::size_t start, std::size_t len) const
{
    return StrRef((start < size()) ? (mBegin + start) : mEnd,
                  (start + len) < size() ? (mBegin + start + len) : mEnd);
}

inline
const char& StrRef::operator[](std::size_t n) const
{
    return mBegin[n];
}

inline
bool operator==(const StrRef& lhs, const StrRef& rhs)
{
    if (lhs.size() == rhs.size())
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    return false;
}

inline
bool operator!=(const StrRef& lhs, const StrRef& rhs)
{
    return !(lhs == rhs);
}

#endif
