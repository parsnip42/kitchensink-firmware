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
    EventDispatcher(const std::array<uint8_t, KeyMatrix::kRows>&    rowMapping,
                    const std::array<uint8_t, KeyMatrix::kColumns>& columnMapping);
    
public:
    template <typename Callback>
    void dispatch(const KeyMatrix::Mask& stateMask,
                  const KeyMatrix::Mask& deltaMask,
                  const Callback&        callback);
    
    template <typename Callback>
    void pressed(const KeyMatrix::Mask& stateMask,
                 const Callback&        callback);

private:
    const std::array<uint8_t, KeyMatrix::kRows>    mRowMapping;
    const std::array<uint8_t, KeyMatrix::kColumns> mColumnMapping;

private:
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
};


inline
EventDispatcher::EventDispatcher(const std::array<uint8_t, KeyMatrix::kRows>&    rowMapping,
                                 const std::array<uint8_t, KeyMatrix::kColumns>& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

template <typename Func>
inline
void EventDispatcher::dispatch(const KeyMatrix::Mask& stateMask,
                               const KeyMatrix::Mask& deltaMask,
                               const Func&            callback)
{
    for (int row(0); row < KeyMatrix::kRows; ++row)
    {
        auto state(stateMask[row]);
        auto delta(deltaMask[row]);

        int column(0);
        
        while (!delta.empty() && column < KeyMatrix::kColumns)
        {
            if (delta[0])
            {
                KeyState keyState(
                    static_cast<KeyState>(((int)state[0]) + 1));
                    
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

template <typename Func>
inline
void EventDispatcher::pressed(const KeyMatrix::Mask& stateMask,
                              const Func&            callback)
{
    for (int row(0); row < KeyMatrix::kRows; ++row)
    {
        auto state(stateMask[row]);

        int column(0);
        
        while (!state.empty() && column < KeyMatrix::kColumns)
        {
            if (state[0])
            {
                callback(KeyMatrixEvent(mRowMapping[row],
                                        mColumnMapping[column],
                                        KeyState::kPressed));
            }
            
            state >>= 1;
            ++column;
        }
    }
}

#endif
