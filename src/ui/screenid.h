#ifndef INCLUDED_SCREENID_H
#define INCLUDED_SCREENID_H

#include <cstdint>

class ScreenId
{
public:
    enum class Type : uint8_t
    {
        kHome      = 0,
        kMenu      = 1,
        kScreen    = 2,
        kEditMacro = 3
    };

public:
    ScreenId() = default;
    
    constexpr ScreenId(Type nType,
                       int  nIndex);
    
public:
    int  index;
    Type type;
};

bool operator==(const ScreenId& lhs, const ScreenId& rhs);
bool operator!=(const ScreenId& lhs, const ScreenId& rhs);


inline
constexpr ScreenId::ScreenId(Type nType,
                             int  nIndex)
    : index(nIndex)
    , type(nType)
{ }

inline
bool operator==(const ScreenId& lhs, const ScreenId& rhs)
{
    return (lhs.type == rhs.type) && (lhs.index == rhs.index);
}

inline
bool operator!=(const ScreenId& lhs, const ScreenId& rhs)
{
    return !(lhs == rhs);
}

#endif
