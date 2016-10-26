#ifndef INCLUDED_EVENTDISPATCHER_H
#define INCLUDED_EVENTDISPATCHER_H

#include "keymask.h"
#include "keymatrixevent.h"

#include <array>
#include <initializer_list>

class KeyMatrix;
class KeyMatrixEvent;

class EventDispatcher
{
public:
    EventDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                    const std::array<uint8_t, KeyMask::kColumns>& columnMapping);
    
public:
    template <typename Callback>
    void dispatch(const KeyMask& stateMask,
                  const KeyMask& deltaMask,
                  const Callback&        callback);
    
    template <typename Callback>
    void pressed(const KeyMask& stateMask,
                 const Callback&        callback);

private:
    const std::array<uint8_t, KeyMask::kRows>    mRowMapping;
    const std::array<uint8_t, KeyMask::kColumns> mColumnMapping;

private:
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
};


inline
EventDispatcher::EventDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                                 const std::array<uint8_t, KeyMask::kColumns>& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

template <typename Func>
inline
void EventDispatcher::dispatch(const KeyMask& stateMask,
                               const KeyMask& deltaMask,
                               const Func&    callback)
{
    for (std::size_t row(0); row < KeyMask::kRows; ++row)
    {
        auto state(stateMask[row]);
        auto delta(deltaMask[row]);

        std::size_t column(0);
        
        while (!delta.empty() && column < KeyMask::kColumns)
        {
            if (delta[0])
            {
                callback(KeyMatrixEvent(mRowMapping[row],
                                        mColumnMapping[column],
                                        state[0]));
            }
            
            state >>= 1;
            delta >>= 1;
            ++column;
        }
    }
}

template <typename Func>
inline
void EventDispatcher::pressed(const KeyMask& stateMask,
                              const Func&    callback)
{
    for (std::size_t row(0); row < KeyMask::kRows; ++row)
    {
        auto state(stateMask[row]);

        std::size_t column(0);
        
        while (!state.empty() && column < KeyMask::kColumns)
        {
            if (state[0])
            {
                callback(KeyMatrixEvent(mRowMapping[row],
                                        mColumnMapping[column],
                                        true));
            }
            
            state >>= 1;
            ++column;
        }
    }
}

#endif
