#include "actions.h"
#include "actioncontext.h"
#include "keyid.h"
#include "keystate.h"
#include "layerstack.h"
#include "usbkeyboard.h"

namespace Actions
{

ActionFunc layerModifier(LayerStack& layerStack, int layer)
{
    return [&layerStack, layer](const ActionContext& context)
    {
        if (context.state == KeyState::kPressed)
        {
            layerStack.setLayer(layer, true);
        }
        else if (context.state == KeyState::kReleased)
        {
            layerStack.setLayer(layer, false);
        }
    };
}

ActionFunc toggleLayer(LayerStack& layerStack, int layer)
{
    return [&layerStack, layer](const ActionContext& context)
    {
        if (context.state == KeyState::kPressed)
        {
            layerStack.setLayer(layer, !layerStack.enabled(layer));
        }
    };
}

ActionFunc modifierKey(UsbKeyboard& usbKeyboard,
                       const KeyId& modifier,
                       const KeyId& key)
{
    return [&usbKeyboard, modifier, key](const ActionContext& context)
    {
        if (context.state != KeyState::kReleased)
        {
            usbKeyboard.setModifier(modifier.value());
            usbKeyboard.setKey(key.value());
        }
        
        if (context.state != KeyState::kHeld)
        {
            usbKeyboard.markDirty();
        }
    };
}

}
