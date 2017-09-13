#ifndef INCLUDED_EVENT_H
#define INCLUDED_EVENT_H

#include <cstdint>

// Invertible;
// TTTT SSSI VVVV VVVV
//
// T = Type
// S = SubType
// I = Inversion bit
// V = Value
//
// Non-Invertible;
// TTTT SSSS VVVV VVVV
//
// T = Type
// S = SubType
// V = Value

class Event
{
public:
    enum class Type : uint8_t
    {

        // Invertible
        kKey        = 0,
        kLayer      = 1,
        kMulti      = 2,
        kSmart      = 3,
        kMacro      = 4,
        kSMacro     = 5,
        
        // Non-invertible
        kTick       = 7,
        kAction     = 8,
        kDelay      = 9,
        kScreen     = 10,
        kLedMask    = 11,
        kInvalidate = 12,  
    };

public:
    static constexpr int      kTypeOffset    = 12;
    static constexpr int      kSubTypeOffset = 8;
    static constexpr uint16_t kSubTypeMask   = 0xf;
    static constexpr uint16_t kValueMask     = 0xff;

public:
    constexpr Event();

    constexpr Event(Type    type,
                    uint8_t value);
    
    constexpr Event(Type    type,
                    uint8_t subType,
                    uint8_t value);

public:
    constexpr Type type() const;

    constexpr bool inverted() const;
    
    constexpr uint8_t subType() const;
    
    constexpr uint8_t value() const;

public:
    template <typename T>
    constexpr bool is() const;
    
    template <typename T>
    constexpr T get() const;

    constexpr bool invertible() const;

    constexpr Event invert() const;

    constexpr bool isUserEvent() const;

private:
    uint16_t mData;

private:
    friend constexpr bool operator==(const Event& lhs, const Event& rhs);
};


inline
constexpr bool operator==(const Event& lhs, const Event& rhs)
{
    return lhs.mData == rhs.mData;
}

inline
constexpr bool operator!=(const Event& lhs, const Event& rhs)
{
    return !(lhs == rhs);
}


inline
constexpr Event::Event()
    : mData(0)
{ }

inline
constexpr Event::Event(Type    type,
                       uint8_t value)
    : Event(type, 0, value)
{ }

inline
constexpr Event::Event(Type    type,
                       uint8_t subType,
                       uint8_t value)
    : mData(static_cast<uint16_t>(type) << kTypeOffset |
            (((static_cast<uint16_t>(subType) << invertible()) & kSubTypeMask) << kSubTypeOffset) |
            (value & kValueMask))
{ }

inline
constexpr Event::Type Event::type() const
{
    return static_cast<Type>(mData >> 12);
}

inline
constexpr uint8_t Event::subType() const
{
    return ((mData >> 8) & kSubTypeMask) >> !invertible();
}

inline
constexpr uint8_t Event::value() const
{
    return mData & kValueMask;
}

template <typename T>
inline
constexpr bool Event::is() const
{
    return T::kType == type();
}
    
template <typename T>
inline
constexpr T Event::get() const
{
    return T(*this);
}

inline
constexpr bool Event::invertible() const
{
    return type() < Type::kTick;
}

inline
constexpr bool Event::inverted() const
{
    return invertible() && (subType() & 1);
}

inline
constexpr Event Event::invert() const
{
    if (invertible())
    {
        Event e(*this);
        
        e.mData ^= (1 << kSubTypeOffset);

        return e;
    }
    else
    {
        return Event();
    }
}

inline
constexpr bool Event::isUserEvent() const
{
    // This event was created directly as a result of user interaction with the
    // device.
    auto t(type());

    return (t == Type::kKey ||
            t == Type::kLayer ||
            t == Type::kMulti ||
            t == Type::kSmart ||
            t == Type::kMacro ||
            t == Type::kSMacro ||
            t == Type::kAction ||
            t == Type::kScreen);
}

#endif
