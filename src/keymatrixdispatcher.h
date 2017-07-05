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
        const auto& state(stateMask[row]);
        const auto& delta(deltaMask[row]);

        auto deltaIterator(delta.bitIterator());
        
        while (deltaIterator.more())
        {
            auto column(deltaIterator.next());

            if (column < KeyMask::kColumns)
            {
                callback(KeyMatrixEvent(mRowMapping[row],
                                        mColumnMapping[column],
                                        state[column]));
            }
        }
    }
}

#endif
