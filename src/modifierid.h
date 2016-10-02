#ifndef INCLUDED_MODIFIERID_H
#define INCLUDED_MODIFIERID_H

#include <cstdint>

class ModifierId
{
public:
    static const ModifierId None;
    static const ModifierId LCtrl;
    static const ModifierId LShift;
    static const ModifierId LAlt;
    static const ModifierId LGui;
    static const ModifierId RCtrl;
    static const ModifierId RShift;
    static const ModifierId RAlt;
    static const ModifierId RGui;
    static ModifierId Layer(int layer);

private:
    explicit ModifierId(uint8_t data);

public:
    uint8_t value() const;
    
private:
    uint8_t mData;

private:
    friend bool operator==(const ModifierId& lhs, const ModifierId& rhs);
};


inline
bool operator==(const ModifierId& lhs, const ModifierId& rhs)
{
    return (lhs.mData == rhs.mData);
}

inline
bool operator!=(const ModifierId& lhs, const ModifierId& rhs)
{
    return !(lhs == rhs);
}


inline
ModifierId ModifierId::Layer(int layer)
{
    return ModifierId(static_cast<uint8_t>(layer + 8));
}

inline
ModifierId::ModifierId(uint8_t data)
    : mData(data)
{ }

inline
uint8_t ModifierId::value() const
{
    return mData;
}

#endif
