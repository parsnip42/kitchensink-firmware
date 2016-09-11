#include "keymatrixeventdispatcher.h"

#include "keymatrix.h"
#include "keymatrixevent.h"
#include "keystate.h"

KeyMatrixEventDispatcher::KeyMatrixEventDispatcher(const RowMapping&    rowMapping,
                                                   const ColumnMapping& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

void KeyMatrixEventDispatcher::dispatch(const KeyMatrix& keyMatrix,
                                        const Callback&  callback)
{
    for (int row(0); row < KeyMatrix::Rows; ++row)
    {
        auto state(keyMatrix.state()[row].data());
        auto delta(keyMatrix.delta()[row].data());

        int column(0);
        
        while ((state || delta) && column < KeyMatrix::Columns)
        {
            KeyState::Value keyState(KeyState::fromMatrix(state & 1, delta & 1));
            
            if (keyState)
            {
                callback(KeyMatrixEvent(mRowMapping[row],
                                        mColumnMapping[column],
                                        keyState));
            }
            
            state>>=1;
            delta>>=1;
            ++column;
        }
    }
}
