#ifndef INCLUDED_EVENT_H
#define INCLUDED_EVENT_H

#include <cstdint>

class Event
{
public:
    enum class Type : uint8_t
    {
        kKey        = 0,
        kLayer      = 1,
        kMulti      = 2,
        kSmart      = 3,
        kMacro      = 4,
        kSMacro     = 5,

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

    // FIXME: Remove!
    Event(int value)
        : mData(static_cast<uint16_t>(Type::kKey) << kTypeOffset |
                (value & kValueMask))
    {
        if (value == 0)
        {
            mData = 0;
        }
    }


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
    
    constexpr Event invert() const;
    
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
    : mData(static_cast<uint16_t>(type) << kTypeOffset |
            (value & kValueMask))
{ }

inline
constexpr Event::Event(Type    type,
                       uint8_t subType,
                       uint8_t value)
    : mData(static_cast<uint16_t>(type) << kTypeOffset |
            ((static_cast<uint16_t>(subType) & kSubTypeMask) << kSubTypeOffset) |
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
    return (mData >> 8) & kSubTypeMask;
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
constexpr bool Event::inverted() const
{
    return (type() < Type::kTick) && (subType() != 0);
}

inline
constexpr Event Event::invert() const
{
    if (type() < Type::kTick)
    {
        Event e(*this);
        
        e.mData ^= (kSubTypeMask << kSubTypeOffset);

        return e;
    }
    else
    {
        return Event();
    }
}

#endif
