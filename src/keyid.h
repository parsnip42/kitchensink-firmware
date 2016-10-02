#ifndef INCLUDED_KEYID_H
#define INCLUDED_KEYID_H

#include "modifierid.h"

#include <cstdint>

class KeyId
{
public:
    enum Type
    {
        kKey      = 1,
        kModifier = 2,
        kAction   = 3
    };

public:
    static const KeyId None;
    static KeyId Action(int actionId);

public:
    KeyId();
    KeyId(int keyCode);
    KeyId(const ModifierId& modifier);

private:
    KeyId(uint8_t type, uint8_t value);

public:
    uint8_t type() const;
    uint8_t value() const;
    
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
KeyId::KeyId()
    : mData(0)
{ }

inline
KeyId::KeyId(int keyCode)
    : mData(((keyCode >> 6) & 0xff00) | (keyCode & 0xff))
{ }

inline
KeyId::KeyId(const ModifierId& modifier)
    : mData(2 << 8 | modifier.value())
{ }

inline
KeyId::KeyId(uint8_t type, uint8_t value)
    : mData(type << 8 | value)
{ }

inline
uint8_t KeyId::type() const
{
    return (mData >> 8);
}

inline
uint8_t KeyId::value() const
{
    return (mData & 0xff);
}

#endif
