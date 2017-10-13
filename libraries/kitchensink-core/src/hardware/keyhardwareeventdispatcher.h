#ifndef INCLUDED_KEYHARDWAREEVENTDISPATCHER_H
#define INCLUDED_KEYHARDWAREEVENTDISPATCHER_H

#include "hardware/keyhardwareevent.h"
#include "hardware/keyhardwareeventhandler.h"

#include <array>

template <typename KeyMask>
class KeyHardwareEventDispatcher
{
public:
    KeyHardwareEventDispatcher(const std::array<uint8_t, KeyMask::kColumns>& columnMapping,
                               const std::array<uint8_t, KeyMask::kRows>&    rowMapping);
    
public:
    void dispatch(const KeyMask&                 stateMask,
                  const KeyMask&                 deltaMask,
                  const KeyHardwareEventHandler& eventHandler);

private:
    const std::array<uint8_t, KeyMask::kColumns> mColumnMapping;
    const std::array<uint8_t, KeyMask::kRows>    mRowMapping;

private:
    KeyHardwareEventDispatcher(const KeyHardwareEventDispatcher&) = delete;
    KeyHardwareEventDispatcher& operator=(const KeyHardwareEventDispatcher&) = delete;
};


template <typename KeyMask>
inline
KeyHardwareEventDispatcher<KeyMask>::KeyHardwareEventDispatcher(const std::array<uint8_t, KeyMask::kColumns>& columnMapping,
                                                                const std::array<uint8_t, KeyMask::kRows>&    rowMapping)
    : mColumnMapping(columnMapping)
    , mRowMapping(rowMapping)
{ }

template <typename KeyMask>
inline
void KeyHardwareEventDispatcher<KeyMask>::dispatch(const KeyMask&                 stateMask,
                                                   const KeyMask&                 deltaMask,
                                                   const KeyHardwareEventHandler& eventHandler)
{
    for (std::size_t row(0); row < KeyMask::kRows; ++row)
    {
        const auto& state(stateMask[row]);
        const auto& delta(deltaMask[row]);

        auto deltaIterator(delta.bitIterator());
        
        while (deltaIterator.more())
        {
            auto column(deltaIterator.next());

            if (column < KeyMask::kColumns)
            {
                eventHandler.processKeyHardwareEvent(KeyHardwareEvent(mRowMapping[row],
                                                                      mColumnMapping[column],
                                                                      state[column]));
            }
        }
    }
}


#endif
