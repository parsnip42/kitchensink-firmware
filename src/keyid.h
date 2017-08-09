#ifndef INCLUDED_KEYID_H
#define INCLUDED_KEYID_H

#include "screenid.h"

#include <cstdint>

class KeyId
{
public:
    enum class Type : uint8_t
    {
        kKey    = 0,
        kLayer  = 1,
        kTick   = 2,
        kMacro  = 3,
        kSMacro = 4,
        kAction = 5,
        kDelay  = 6,
        kMulti  = 7,
        kSmart  = 8,
        kScreen = 9
    };

public:
    static constexpr KeyId Action(int actionId);
    static constexpr KeyId Layer(int layerId);
    static constexpr KeyId Lock(int lockId);
    static constexpr KeyId Macro(int macroId);
    static constexpr KeyId SMacro(int macroId);
    static constexpr KeyId Multi(int multiId);
    static constexpr KeyId Delay(uint32_t delayMs);
    static constexpr KeyId Tick(uint32_t tickId);
    static constexpr KeyId Smart(int keyId);
    static constexpr KeyId Screen(ScreenId::Type type, int index);

public:
    constexpr KeyId(int keyCode = 0);
    
private:
    constexpr KeyId(Type type, uint8_t value);
    constexpr KeyId(Type type, uint8_t subType, uint8_t value);

public:
    constexpr Type type() const;
    constexpr uint8_t subType() const;
    constexpr uint8_t value() const;

    constexpr uint32_t delayMs() const;
    constexpr uint32_t tickId() const;
    constexpr ScreenId::Type screenType() const;

private:
    uint8_t mType;
    uint8_t mValue;
    
private:
    friend constexpr bool operator==(const KeyId& lhs, const KeyId& rhs);
};


inline
constexpr bool operator==(const KeyId& lhs, const KeyId& rhs)
{
    return (lhs.mType == rhs.mType) && (lhs.mValue == rhs.mValue);
}

inline
constexpr bool operator!=(const KeyId& lhs, const KeyId& rhs)
{
    return !(lhs == rhs);
}


inline
constexpr KeyId KeyId::Action(int actionId)
{
    return KeyId(Type::kAction, actionId);
}

inline
constexpr KeyId KeyId::Layer(int layerId)
{
    return KeyId(Type::kLayer, layerId);
}

inline
constexpr KeyId KeyId::Multi(int multiId)
{
    return KeyId(Type::kMulti, multiId);
}

inline
constexpr KeyId KeyId::Macro(int macroId)
{
    return KeyId(Type::kMacro, macroId);
}

inline
constexpr KeyId KeyId::SMacro(int macroId)
{
    return KeyId(Type::kSMacro, macroId);
}

inline
constexpr KeyId KeyId::Delay(uint32_t delayMs)
{
    return KeyId(Type::kDelay,
                 (delayMs >> 8) & 0xf,
                 delayMs & 0xff);
}

inline
constexpr KeyId KeyId::Tick(uint32_t tickId)
{
    return KeyId(Type::kTick,
                 (tickId >> 8) & 0xf,
                 tickId & 0xff);
}

inline
constexpr KeyId KeyId::Smart(int keyId)
{
    return KeyId(Type::kSmart, keyId);
}

inline
constexpr KeyId KeyId::Screen(ScreenId::Type type, int index)
{
    return KeyId(Type::kScreen,
                 static_cast<uint8_t>(type),
                 index);
}

inline
constexpr KeyId::KeyId(int keyCode)
    : mType(0)
    , mValue(keyCode & 0xff)
{ }

inline
constexpr KeyId::KeyId(Type type, uint8_t value)
    : mType((static_cast<uint8_t>(type) & 0xf) << 4)
    , mValue(value)
{ }

inline
constexpr KeyId::KeyId(Type type, uint8_t subType, uint8_t value)
    : mType((static_cast<uint8_t>(type) & 0xf) << 4 | (subType & 0xf))
    , mValue(value)
{ }


inline
constexpr KeyId::Type KeyId::type() const
{
    return Type((mType >> 4) & 0xf);
}

inline
constexpr uint8_t KeyId::subType() const
{
    return mType & 0xf;
}

inline
constexpr uint8_t KeyId::value() const
{
    return mValue;
}

inline
constexpr uint32_t KeyId::delayMs() const
{
    return (subType() << 8) | value();
}

inline
constexpr uint32_t KeyId::tickId() const
{
    return (subType() << 8) | value();
}

inline
constexpr ScreenId::Type KeyId::screenType() const
{
    return static_cast<ScreenId::Type>(subType());
}

#endif
