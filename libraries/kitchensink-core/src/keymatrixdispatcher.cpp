#include "keymatrixdispatcher.h"

KeyMatrixDispatcher::KeyMatrixDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                                         const std::array<uint8_t, KeyMask::kColumns>& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

void KeyMatrixDispatcher::dispatch(const KeyMask&               stateMask,
                                   const KeyMask&               deltaMask,
                                   const KeyMatrixEventHandler& eventHandler)
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
                eventHandler.processKeyMatrixEvent(KeyMatrixEvent(mRowMapping[row],
                                                                  mColumnMapping[column],
                                                                  state[column]));
            }
        }
    }
}

