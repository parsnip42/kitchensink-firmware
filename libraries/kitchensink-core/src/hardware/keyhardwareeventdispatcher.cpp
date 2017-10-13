#include "hardware/keyhardwareeventdispatcher.h"

KeyHardwareEventDispatcher::KeyHardwareEventDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                                                       const std::array<uint8_t, KeyMask::kColumns>& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

void KeyHardwareEventDispatcher::dispatch(const KeyMask&                 stateMask,
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

