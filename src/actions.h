#ifndef INCLUDED_ACTIONS_H
#define INCLUDED_ACTIONS_H

#include <functional>

class ActionContext;
class KeyId;
class LayerStack;
class UsbKeyboard;

namespace Actions
{

typedef std::function<void(const ActionContext&)> ActionFunc;

ActionFunc layerModifier(LayerStack& layerStack, int layer);
ActionFunc toggleLayer(LayerStack& layerStack, int layer);
ActionFunc modifierKey(UsbKeyboard& usbKeyboard,
                       const KeyId& modifier,
                       const KeyId& key);

}

#endif
