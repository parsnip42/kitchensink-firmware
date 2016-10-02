#include "eventdispatcher.h"

#include "keymatrix.h"
#include "keymatrixevent.h"
#include "keystate.h"

EventDispatcher::EventDispatcher(const std::initializer_list<int>& rowMapping,
                                 const std::initializer_list<int>& columnMapping)
{
    mRowMapping.fill(0);

    size_t row(0);

    for (auto& index : rowMapping)
    {
        mRowMapping[row++] = index;
    }

    mColumnMapping.fill(0);

    size_t column(0);

    for (auto& index : columnMapping)
    {
        mColumnMapping[column++] = index;
    }
}

void EventDispatcher::dispatch(const KeyMatrix::Mask& stateMask,
                               const KeyMatrix::Mask& deltaMask,
                               const Callback&        callback)
{
    for (int row(0); row < KeyMatrix::kRows; ++row)
    {
        auto state(stateMask[row].data());
        auto delta(deltaMask[row].data());

        int column(0);
        
        while ((state || delta) && column < KeyMatrix::kColumns)
        {
            KeyState::Value keyState(KeyState::fromMatrix(state & 1, delta & 1));
            
            if (keyState)
            {
                callback(KeyMatrixEvent(mRowMapping[row],
                                        mColumnMapping[column],
                                        keyState));
            }
            
            state >>= 1;
            delta >>= 1;
            ++column;
        }
    }
}
