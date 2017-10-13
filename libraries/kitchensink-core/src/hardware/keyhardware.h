#ifndef INCLUDED_KEYHARDWARE_H
#define INCLUDED_KEYHARDWARE_H

#include <cstdint>

class KeyHardwareEventHandler;

class KeyHardware
{
public:
    virtual void poll(uint32_t                       timeMs,
                      const KeyHardwareEventHandler& handler) = 0;

    virtual void pressed(const KeyHardwareEventHandler& handler) = 0;
    
    virtual bool any() const = 0;
};

#endif
