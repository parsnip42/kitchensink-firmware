#ifndef INCLUDED_KEYID_H
#define INCLUDED_KEYID_H

#include <cstdint>

class KeyId
{
public:
    enum class Type : uint8_t
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
        kHold              = 0,
        kToggle            = 1,
        kDoubleLock        = 2,
        kTripleLock        = 3,
        kSingle            = 4,
        kSingleHold        = 5,
        kSingleHoldRelease = 6,
    };

    enum class MacroType : uint8_t
    {
        kSync   = 0,
        kASync  = 1,
        kInvert = 2
    };
    
    enum class ActionType : uint8_t
    {
        kBuiltIn = 0,
        kMenu    = 1
    };

public:
    static const KeyId None;
    static constexpr KeyId Action(ActionType actionType,
                                  int        actionId);
    static constexpr KeyId Layer(int layerId);
    static constexpr KeyId Multi(int multiId);
    static constexpr KeyId Modifier(ModifierType modifierType,
                                    int          modifierId);
    static constexpr KeyId Modifier(int modifierId);
    static constexpr KeyId Macro(MacroType macroType,
                                 int       macroId);
    
public:
    constexpr KeyId(int keyCode = 0);
    
private:
    constexpr KeyId(Type type, uint8_t value);
    constexpr KeyId(Type type, uint8_t subType, uint8_t value);

public:
    Type type() const;
    uint8_t subType() const;
    uint8_t value() const;

    ActionType actionType() const;
    ModifierType modifierType() const;
    MacroType macroType() const;
    
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
constexpr KeyId KeyId::Multi(int multiId)
{
    return KeyId(Type::kMulti, multiId);
}

inline
constexpr KeyId KeyId::Modifier(int modifierId)
{
    return KeyId(Type::kModifier,
                 static_cast<uint8_t>(ModifierType::kHold),
                 modifierId);
}

inline
constexpr KeyId KeyId::Modifier(ModifierType modifierType,
                                int          modifierId)
{
    return KeyId(Type::kModifier,
                 static_cast<uint8_t>(modifierType),
                 modifierId);
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
KeyId::Type KeyId::type() const
{
    return Type((mData >> 12) & 0xf);
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
KeyId::ActionType KeyId::actionType() const
{
    return static_cast<KeyId::ActionType>(subType());
}

inline
KeyId::ModifierType KeyId::modifierType() const
{
    return static_cast<KeyId::ModifierType>(subType());
}

inline
KeyId::MacroType KeyId::macroType() const
{
    return static_cast<KeyId::MacroType>(subType());
}

#endif
