#ifndef INCLUDED_KEYBOARDPLATE_H
#define INCLUDED_KEYBOARDPLATE_H

#include "hardware/debounce.h"
#include "hardware/keyhardware.h"
#include "hardware/keyhardwareeventdispatcher.h"
#include "types/bitmask2d.h"

#include <cstdint>

class EntropyPool;
class KeyHardwareEventHandler;

template <typename KeyDriver, std::size_t Columns, std::size_t Rows>
class KeyboardPlate : public KeyHardware
{
public:
    KeyboardPlate(KeyDriver&                          keyDriver,
                  const std::array<uint8_t, Columns>& columnMapping,
                  const std::array<uint8_t, Rows>&    rowMapping);

public:
    virtual void poll(uint32_t                       timeMs,
                      const KeyHardwareEventHandler& eventHandler) override;

    virtual void pressed(const KeyHardwareEventHandler& eventHandler) override;
    
    virtual bool any() const override;
    
private:
    typedef Bitmask2d<Columns, Rows> KeyMask;

private:
    KeyMask                             mState;
    KeyDriver&                          mKeyDriver;
    Debounce<KeyMask>                   mDebounce;
    KeyHardwareEventDispatcher<KeyMask> mDispatcher;

private:
    KeyboardPlate(const KeyboardPlate&) = delete;
    KeyboardPlate& operator=(const KeyboardPlate&) = delete;
};


template <typename KeyDriver, std::size_t Columns, std::size_t Rows>
inline
KeyboardPlate<KeyDriver, Columns, Rows>::KeyboardPlate(KeyDriver&                          keyDriver,
                                                       const std::array<uint8_t, Columns>& columnMapping,
                                                       const std::array<uint8_t, Rows>&    rowMapping)
    : mKeyDriver(keyDriver)
    , mDebounce()
    , mDispatcher(columnMapping,
                  rowMapping)
{ }

template <typename KeyDriver, std::size_t Columns, std::size_t Rows>
inline
void KeyboardPlate<KeyDriver, Columns, Rows>::poll(uint32_t                       timeMs,
                                                   const KeyHardwareEventHandler& eventHandler)
{
    mKeyDriver.scan(mState);
    
    if (mDebounce.process(timeMs, mState))
    {
        mDispatcher.dispatch(mDebounce.state,
                             mDebounce.delta,
                             eventHandler);
    }
}

template <typename KeyDriver, std::size_t Columns, std::size_t Rows>
inline
void KeyboardPlate<KeyDriver, Columns, Rows>::pressed(const KeyHardwareEventHandler& eventHandler)
{
    mDispatcher.dispatch(KeyMask(),
                         mDebounce.state,
                         eventHandler);
}

template <typename KeyDriver, std::size_t Columns, std::size_t Rows>
inline
bool KeyboardPlate<KeyDriver, Columns, Rows>::any() const
{
    return !mDebounce.state.empty() || !mDebounce.delta.empty();
}

#endif
