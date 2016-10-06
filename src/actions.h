#ifndef INCLUDED_ACTIONS_H
#define INCLUDED_ACTIONS_H

#include <functional>

class ActionContext;
class KeyId;
class KsKeyboard;
class UsbKeyboard;

namespace Actions
{

typedef std::function<void(const ActionContext&)> ActionFunc;

// ActionFunc layerModifier(KsKeyboard& keyboard, int layer);
// ActionFunc toggleLayer(KsKeyboard& keyboard, int layer);
// ActionFunc modifierKey(UsbKeyboard& usbKeyboard,
//                        const KeyId& modifier,
//                        const KeyId& key);

}

#endif
