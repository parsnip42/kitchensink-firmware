#include "keymatrixeventdispatcher.h"

#include "keymatrix.h"
#include "keymatrixevent.h"
#include "keystate.h"

KeyMatrixEventDispatcher::KeyMatrixEventDispatcher(const RowMapping&    rowMapping,
                                                   const ColumnMapping& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

void KeyMatrixEventDispatcher::dispatch(const KeyMatrix::Mask& stateMask,
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
