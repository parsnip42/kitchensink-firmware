#include "keyhandler.h"

#include "kskeyboard.h"

KeyHandler::KeyHandler(KsKeyboard& keyboard)
    : mKeyboard(keyboard)
    , mLayerStack()
    , mModifierSet()
    , mTapping(500)
    , mModifierMask(0)
{
    mLayerStack.setLayer(0, true);
}

void KeyHandler::assignLayer(int index, const Layer& layer)
{
    mLayerStack.assignLayer(index, layer);
}

void KeyHandler::setLayer(int index, bool enabled)
{
    mLayerStack.setLayer(index, enabled);
}

bool KeyHandler::layerEnabled(int layer) const
{
    return mLayerStack.enabled(layer);
}
