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
        kHold    = 0,
        kToggle  = 1,
        kSingle  = 2
    };
    
public:
    static const KeyId None;
    static constexpr KeyId Action(int actionId);
    static constexpr KeyId Layer(int layerId);
    static constexpr KeyId Multi(int multiId);
    static constexpr KeyId Modifier(ModifierType modifierType,
                                    int          modifierId);
    
public:
    constexpr KeyId(int keyCode = 0);
    
private:
    constexpr KeyId(Type type, uint8_t value);
    constexpr KeyId(Type type, uint8_t subType, uint8_t value);

public:
    Type type() const;
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
constexpr KeyId KeyId::Modifier(ModifierType modifierType,
                                int          modifierId)
{
    return KeyId(Type::kModifier,
                 static_cast<uint8_t>(modifierType),
                 modifierId);
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
KeyId::ModifierType KeyId::modifierType() const
{
    return static_cast<KeyId::ModifierType>(subType());
}

#endif
