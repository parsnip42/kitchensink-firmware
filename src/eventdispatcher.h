#ifndef INCLUDED_EVENTDISPATCHER_H
#define INCLUDED_EVENTDISPATCHER_H

#include "keymatrix.h"

#include "keymatrix.h"
#include "keymatrixevent.h"
#include "keystate.h"

#include <array>
#include <initializer_list>

class KeyMatrix;
class KeyMatrixEvent;

class EventDispatcher
{
public:
    EventDispatcher(const std::initializer_list<int>& rowMapping,
                    const std::initializer_list<int>& columnMapping);

public:
    template <typename Callback>
    void dispatch(const KeyMatrix::Mask& stateMask,
                  const KeyMatrix::Mask& deltaMask,
                  const Callback&        callback);

private:
    std::array<int, KeyMatrix::kRows>    mRowMapping;
    std::array<int, KeyMatrix::kColumns> mColumnMapping;

private:
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
};


template <typename Func>
inline
void EventDispatcher::dispatch(const KeyMatrix::Mask& stateMask,
                               const KeyMatrix::Mask& deltaMask,
                               const Func&            callback)
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

#endif
