#include "kskeyboard.h"

KsKeyboard::KsKeyboard()
    : mLeft(0x20, 0x7C00, 0x3FF, 3,
            {4,3,2,1,0},
            {0,1,2,3,4,5,6,7,9,8,10,11,12,13,14,15})
    , mRight(0x21, 0x3E00, 0xC0FF, 3,
             {0,1,2,3,4},
             {12,13,14,15,16,17,18,19,20,21,22,23,24,25,11,10})
    , mLayerStack()
    , mTapping(500)
{
    mLayerStack.setLayer(0, true);
}

void KsKeyboard::assignLayer(const Layer* layer, int index)
{
    mLayerStack.assignLayer(layer, index);
}

void KsKeyboard::setLayer(int index, bool enabled)
{
    mLayerStack.setLayer(index, enabled);
}

bool KsKeyboard::enabled(int layer) const
{
    return mLayerStack.enabled(layer);
}

bool KsKeyboard::scan()
{
    bool hasEvent(false);
        
    hasEvent |= mLeft.scan();
    hasEvent |= mRight.scan();

    return hasEvent;
}

KsKeyboard::Event KsKeyboard::processKeyMatrixEvent(const KeyMatrixEvent& event)
{
    auto keyId(mLayerStack.at(event.row, event.column));
    
    if (event.state == KeyState::kPressed)
    {
        mTapping.processKey(keyId);
    }
    
    return Event(keyId,
                 event.state,
                 mTapping.count(keyId));
}

