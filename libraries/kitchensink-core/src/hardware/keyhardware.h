#ifndef INCLUDED_KEYHARDWARE_H
#define INCLUDED_KEYHARDWARE_H

#include <cstdint>

class KeyMatrixEventHandler;

class KeyHardware
{
public:
    virtual void poll(uint32_t                     timeMs,
                      const KeyMatrixEventHandler& callback) = 0;

    virtual void pressed(const KeyMatrixEventHandler& callback) = 0;
    
    virtual bool any() const = 0;
};

#endif
