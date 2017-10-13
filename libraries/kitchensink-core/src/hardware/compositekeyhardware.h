#ifndef INCLUDED_COMPOSITEKEYHARDWARE_H
#define INCLUDED_COMPOSITEKEYHARDWARE_H

#include "hardware/keyhardware.h"
#include "hardware/keyhardwareeventhandler.h"

#include <array>
#include <cstdint>

template <std::size_t Size>
class CompositeKeyHardware : public KeyHardware
{
public:
    typedef std::array<KeyHardware*, Size> Entries;

public:
    CompositeKeyHardware(const Entries& entries);

public:
    virtual void poll(uint32_t                       timeMs,
                      const KeyHardwareEventHandler& handler) override;

    virtual void pressed(const KeyHardwareEventHandler& callback) override;
    
    virtual bool any() const override;

private:
    Entries mEntries;

private:
    CompositeKeyHardware(const CompositeKeyHardware&) = delete;
    CompositeKeyHardware& operator=(const CompositeKeyHardware&) = delete;
};


template <std::size_t Size>
inline
CompositeKeyHardware<Size>::CompositeKeyHardware(const Entries& entries)
    : mEntries(entries)
{ }

template <std::size_t Size>
inline
void CompositeKeyHardware<Size>::poll(uint32_t                       timeMs,
                                      const KeyHardwareEventHandler& handler)
{
    for (auto entry : mEntries)
    {
        entry->poll(timeMs, handler);
    }    
}

template <std::size_t Size>
inline
void CompositeKeyHardware<Size>::pressed(const KeyHardwareEventHandler& handler)
{
    for (auto entry : mEntries)
    {
        entry->pressed(handler);
    }    
}

template <std::size_t Size>
inline
bool CompositeKeyHardware<Size>::any() const
{
    bool any(false);

    for (auto entry : mEntries)
    {
        any |= entry->any();
    }    

    return any;
}


#endif
