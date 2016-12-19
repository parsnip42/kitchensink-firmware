#ifndef INCLUDED_STRREF_H
#define INCLUDED_STRREF_H

#include <cstdint>
#include <cstring>

namespace Types
{

class StrRef
{
public:
    typedef const char* const_iterator;
    
public:
    constexpr StrRef(const char* str);
    
public:
    constexpr const_iterator begin() const;
    constexpr const_iterator end() const;
    constexpr std::size_t size() const;

private:
    constexpr std::size_t size(const char* data) const;

private:
    const char* mData;
};


inline
constexpr StrRef::StrRef(const char* str)
    : mData(str)
{ }

inline
constexpr StrRef::const_iterator StrRef::begin() const
{
    return mData;
}

inline
constexpr StrRef::const_iterator StrRef::end() const
{
    return mData + size();
}

inline
constexpr std::size_t StrRef::size() const
{
    return size(mData);
}

inline
constexpr std::size_t StrRef::size(const char* data) const
{
    return (data[0] == '\0') ? 0 : (1 + size(data + 1));
}

}

#endif
