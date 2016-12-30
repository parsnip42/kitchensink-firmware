#ifndef INCLUDED_KEYMATRIXDISPATCHER_H
#define INCLUDED_KEYMATRIXDISPATCHER_H

#include "keymask.h"
#include "keymatrixevent.h"

#include <array>
#include <initializer_list>

class KeyMatrix;
class KeyMatrixEvent;

class KeyMatrixDispatcher
{
public:
    constexpr KeyMatrixDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                                  const std::array<uint8_t, KeyMask::kColumns>& columnMapping);
    
public:
    template <typename Callback>
    void dispatch(const KeyMask&  stateMask,
                  const KeyMask&  deltaMask,
                  const Callback& callback);

private:
    const std::array<uint8_t, KeyMask::kRows>    mRowMapping;
    const std::array<uint8_t, KeyMask::kColumns> mColumnMapping;

private:
    KeyMatrixDispatcher(const KeyMatrixDispatcher&) = delete;
    KeyMatrixDispatcher& operator=(const KeyMatrixDispatcher&) = delete;
};


inline
constexpr KeyMatrixDispatcher::KeyMatrixDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                                                   const std::array<uint8_t, KeyMask::kColumns>& columnMapping)
    : mRowMapping(rowMapping)
    , mColumnMapping(columnMapping)
{ }

template <typename Func>
inline
void KeyMatrixDispatcher::dispatch(const KeyMask& stateMask,
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

#endif
