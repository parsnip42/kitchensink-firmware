#ifndef INCLUDED_KEYHARDWAREEVENTDISPATCHER_H
#define INCLUDED_KEYHARDWAREEVENTDISPATCHER_H

#include "hardware/keymask.h"
#include "hardware/keyhardwareevent.h"
#include "hardware/keyhardwareeventhandler.h"

#include <array>

class KeyHardwareEventDispatcher
{
public:
    KeyHardwareEventDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                               const std::array<uint8_t, KeyMask::kColumns>& columnMapping);
    
public:
    void dispatch(const KeyMask&                 stateMask,
                  const KeyMask&                 deltaMask,
                  const KeyHardwareEventHandler& eventHandler);

private:
    const std::array<uint8_t, KeyMask::kRows>    mRowMapping;
    const std::array<uint8_t, KeyMask::kColumns> mColumnMapping;

private:
    KeyHardwareEventDispatcher(const KeyHardwareEventDispatcher&) = delete;
    KeyHardwareEventDispatcher& operator=(const KeyHardwareEventDispatcher&) = delete;
};

#endif
