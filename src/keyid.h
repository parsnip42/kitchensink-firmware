#ifndef INCLUDED_KEYID_H
#define INCLUDED_KEYID_H

#include <cstdint>

class KeyId
{
public:
    enum Type
    {
        kKey      = 0,
        kLayer    = 1,
        kModifier = 2,
        kMulti    = 3,
        kMacro    = 4,
        kSMacro   = 5,
        kAction   = 6
    };

    enum class ModifierType : uint8_t
    {
        kHold    = 0,
        kToggle  = 1,
        kSingle  = 2
    };
    
public:
    static const KeyId None;
    static KeyId Action(int actionId);
    static KeyId Layer(int layerId);
    static KeyId Multi(int multiId);
    static KeyId Modifier(ModifierType modifierType,
                          int          modifierId);
    
public:
    KeyId();
    KeyId(int keyCode);
    
private:
    KeyId(uint8_t type, uint8_t value);
    KeyId(uint8_t type, uint8_t subType, uint8_t value);

public:
    uint8_t type() const;
    uint8_t subType() const;
    uint8_t value() const;

    ModifierType modifierType() const;
    
private:
    uint16_t mData;

private:
    friend bool operator==(const KeyId& lhs, const KeyId& rhs);
};


inline
bool operator==(const KeyId& lhs, const KeyId& rhs)
{
    return (lhs.mData == rhs.mData);
}

inline
bool operator!=(const KeyId& lhs, const KeyId& rhs)
{
    return !(lhs == rhs);
}


inline
KeyId KeyId::Action(int actionId)
{
    return KeyId(kAction, actionId);
}

inline
KeyId KeyId::Layer(int layerId)
{
    return KeyId(kLayer, layerId);
}

inline
KeyId KeyId::Multi(int multiId)
{
    return KeyId(kMulti, multiId);
}

inline
KeyId KeyId::Modifier(ModifierType modifierType,
                      int          modifierId)
{
    return KeyId(kModifier,
                 static_cast<uint8_t>(modifierType),
                 modifierId);
}

inline
KeyId::KeyId()
    : mData(0)
{ }

inline
KeyId::KeyId(int keyCode)
    : mData(keyCode & 0xff)
{ }

inline
KeyId::KeyId(uint8_t type, uint8_t value)
    : mData((type & 0xf) << 12 |
            (value & 0xff))
{ }

inline
KeyId::KeyId(uint8_t type, uint8_t subType, uint8_t value)
    : mData((type & 0xf) << 12 |
            (subType & 0xf) << 8 |
            value)
{ }


inline
uint8_t KeyId::type() const
{
    return (mData >> 12) & 0xf;
}

inline
uint8_t KeyId::subType() const
{
    return (mData >> 8) & 0xf;
}

inline
uint8_t KeyId::value() const
{
    return (mData & 0xff);
}

inline
KeyId::ModifierType KeyId::modifierType() const
{
    return static_cast<KeyId::ModifierType>(subType());
}

#endif
