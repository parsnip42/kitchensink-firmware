#ifndef INCLUDED_KEYID_H
#define INCLUDED_KEYID_H

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
    KeyId();
    KeyId(int keyCode);
    KeyId(uint8_t type, uint8_t value);

public:
    uint8_t type() const;
    uint8_t value() const;
    
private:
    uint16_t mData;
};


inline
KeyId::KeyId()
    : mData(0)
{ }

inline
KeyId::KeyId(int keyCode)
    : mData(((keyCode >> 6) & 0xff00) | (keyCode & 0xff))
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
