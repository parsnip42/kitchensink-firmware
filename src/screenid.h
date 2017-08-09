#ifndef INCLUDED_SCREENID_H
#define INCLUDED_SCREENID_H

class ScreenId
{
public:
    enum class Type
    {
        kHome           = 0,
        kMenu           = 1,
        kScreen         = 2,
        kEditMacro      = 3,
        kEditSMacro     = 4,
        kRecordMacro    = 5,
        kRecordMacroRT  = 6,
        kRecordSMacro   = 7,
        kRecordSMacroRT = 8
    };

public:
    ScreenId() = default;
    
    constexpr ScreenId(Type nType,
                       int  nIndex);
    
public:
    Type type;
    int  index;
};

bool operator==(const ScreenId& lhs, const ScreenId& rhs);
bool operator!=(const ScreenId& lhs, const ScreenId& rhs);


inline
constexpr ScreenId::ScreenId(Type nType,
                             int  nIndex)
    : type(nType)
    , index(nIndex)
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
