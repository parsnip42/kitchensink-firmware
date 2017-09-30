#ifndef INCLUDED_KEYMATRIXDISPATCHER_H
#define INCLUDED_KEYMATRIXDISPATCHER_H

#include "hardware/keymask.h"
#include "keymatrixevent.h"
#include "keymatrixeventhandler.h"

#include <array>
#include <initializer_list>

class KeyMatrixDispatcher
{
public:
    KeyMatrixDispatcher(const std::array<uint8_t, KeyMask::kRows>&    rowMapping,
                        const std::array<uint8_t, KeyMask::kColumns>& columnMapping);
    
public:
    void dispatch(const KeyMask&               stateMask,
                  const KeyMask&               deltaMask,
                  const KeyMatrixEventHandler& eventHandler);

private:
    const std::array<uint8_t, KeyMask::kRows>    mRowMapping;
    const std::array<uint8_t, KeyMask::kColumns> mColumnMapping;

private:
    KeyMatrixDispatcher(const KeyMatrixDispatcher&) = delete;
    KeyMatrixDispatcher& operator=(const KeyMatrixDispatcher&) = delete;
};

#endif
