#include "keyhandler.h"

#include "kskeyboard.h"


KeyHandler::Event::Event(KeyId           nKeyId,
                         KeyState::Value nState,
                         int             nTaps)
    : keyId(nKeyId)
    , state(nState)
    , taps(nTaps)
{ }


KeyHandler::KeyHandler()
    : mLayerStack()
    , mModifierSet()
    , mTapping(500)
{
    mLayerStack.setLayer(0, true);
}

void KeyHandler::assignLayer(const Layer* layer, int index)
{
    mLayerStack.assignLayer(layer, index);
}

void KeyHandler::setLayer(int index, bool enabled)
{
    mLayerStack.setLayer(index, enabled);
}

bool KeyHandler::layerEnabled(int layer) const
{
    return mLayerStack.enabled(layer);
}
