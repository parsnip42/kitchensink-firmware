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
        kAction = 5
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

    enum class MacroType : uint8_t
    {
        kSync   = 0,
        kASync  = 1,
        kInvert = 2
    };
    
    enum class ActionType : uint8_t
    {
        kBuiltIn        = 0,
        kMenu           = 1,
        // kRenameLayer    = 2,
        // kRenameModifier = 3,
        // kRenameMacro    = 4,
        // kRenameSMacro   = 5
    };

public:
    static constexpr KeyId Action(ActionType actionType,
                                  int        actionId);
    static constexpr KeyId Layer(int layerId);
    static constexpr KeyId Lock(LockType lockType,
                                int          lockId);
    static constexpr KeyId Lock(int lockId);
    static constexpr KeyId Macro(MacroType macroType,
                                 int       macroId);
    
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
    constexpr MacroType macroType() const;
    
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
                                int          lockId)
{
    return KeyId(Type::kLock,
                 static_cast<uint8_t>(lockType),
                 lockId);
}

inline
constexpr KeyId KeyId::Macro(MacroType macroType,
                             int       macroId)
{
    return KeyId(Type::kMacro,
                 static_cast<uint8_t>(macroType),
                 macroId);
}

inline
constexpr KeyId::KeyId(int keyCode)
    : mData(keyCode & 0xff)
{ }

inline
constexpr KeyId::KeyId(Type type, uint8_t value)
    : mData((static_cast<uint8_t>(type) & 0xf) << 12 |
            (value & 0xff))
{ }

inline
constexpr KeyId::KeyId(Type type, uint8_t subType, uint8_t value)
    : mData((static_cast<uint8_t>(type) & 0xf) << 12 |
            (subType & 0xf) << 8 |
            value)
{ }


inline
constexpr KeyId::Type KeyId::type() const
{
    return Type((mData >> 12) & 0xf);
}

inline
constexpr uint8_t KeyId::subType() const
{
    return (mData >> 8) & 0xf;
}

inline
constexpr uint8_t KeyId::value() const
{
    return (mData & 0xff);
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
constexpr KeyId::MacroType KeyId::macroType() const
{
    return static_cast<KeyId::MacroType>(subType());
}

#endif
