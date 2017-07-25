#ifndef INCLUDED_KEYID_H
#define INCLUDED_KEYID_H

#include <cstdint>

class KeyId
{
public:
    enum class Type : uint8_t
    {
        kKey    = 0,
        kLayer  = 1,
        kLock   = 2,
        kMacro  = 3,
        kSMacro = 4,
        kAction = 5,
        kDelay  = 6,
        kMulti  = 7,
        kTick   = 8
    };

    enum class LockType : uint8_t
    {
        kHold              = 0, // Standard hold/release
        kToggle            = 1, // Toggle on/off
        kDoubleLock        = 2, // Hold and double tap to lock
        kTripleLock        = 3, // Hold and triple tap to lock
        kSingle            = 4, // Single tap to hold, auto release
        kSingleHold        = 5, // Single tap for one key, hold/release
        kSingleHoldRelease = 6, // Single tap for one key, hold/release for one key
    };

    enum class ActionType : uint8_t
    {
        kBuiltIn   = 0,
        kMenu      = 1,
        kEditMacro = 2
    };

public:
    static constexpr KeyId Action(ActionType actionType,
                                  int        actionId);
    static constexpr KeyId Layer(int layerId);
    static constexpr KeyId Lock(LockType lockType,
                                int      lockId);
    static constexpr KeyId Lock(int lockId);
    static constexpr KeyId Macro(int macroId);
    static constexpr KeyId Multi(int multiId);
    static constexpr KeyId Delay(uint32_t delayMs);
    static constexpr KeyId Tick(uint32_t tickId);

public:
    constexpr KeyId(int keyCode = 0);
    
private:
    constexpr KeyId(Type type, uint8_t value);
    constexpr KeyId(Type type, uint8_t subType, uint8_t value);

public:
    constexpr Type type() const;
    constexpr uint8_t subType() const;
    constexpr uint8_t value() const;

    constexpr ActionType actionType() const;
    constexpr LockType lockType() const;
    constexpr uint32_t delayMs() const;
    constexpr uint32_t tickId() const;

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
constexpr KeyId KeyId::Action(ActionType actionType,
                              int actionId)
{
    return KeyId(Type::kAction,
                 static_cast<uint8_t>(actionType),
                 actionId);
}

inline
constexpr KeyId KeyId::Layer(int layerId)
{
    return KeyId(Type::kLayer, layerId);
}

inline
constexpr KeyId KeyId::Lock(int lockId)
{
    return KeyId(Type::kLock,
                 static_cast<uint8_t>(LockType::kHold),
                 lockId);
}

inline
constexpr KeyId KeyId::Lock(LockType lockType,
                            int      lockId)
{
    return KeyId(Type::kLock,
                 static_cast<uint8_t>(lockType),
                 lockId);
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
constexpr KeyId KeyId::Delay(uint32_t delayMs)
{
    return KeyId(Type::kDelay,
                 (delayMs >> 8) & 0xf,
                 delayMs & 0xff);
}

inline
constexpr KeyId KeyId::Tick(uint32_t tickId)
{
    return KeyId(Type::kDelay,
                 (tickId >> 8) & 0xf,
                 tickId & 0xff);
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
constexpr KeyId::ActionType KeyId::actionType() const
{
    return static_cast<KeyId::ActionType>(subType());
}

inline
constexpr KeyId::LockType KeyId::lockType() const
{
    return static_cast<KeyId::LockType>(subType());
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

#endif
