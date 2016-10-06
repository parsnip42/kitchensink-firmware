#include "actions.h"
#include "actioncontext.h"
#include "keyid.h"
#include "keystate.h"
#include "kskeyboard.h"
#include "usbkeyboard.h"

namespace Actions
{

// ActionFunc layerModifier(KsKeyboard& keyboard, int layer)
// {
//     return [&keyboard, layer](const ActionContext& context)
//     {
//         if (context.state == KeyState::kPressed)
//         {
//             keyboard.setLayer(layer, true);
//         }
//         else if (context.state == KeyState::kReleased)
//         {
//             keyboard.setLayer(layer, false);
//         }
//     };
// }

// ActionFunc toggleLayer(KsKeyboard& keyboard, int layer)
// {
//     return [&keyboard, layer](const ActionContext& context)
//     {
//         if (context.state == KeyState::kPressed)
//         {
//             keyboard.setLayer(layer, !keyboard.layerEnabled(layer));
//         }
//     };
// }

// ActionFunc modifierKey(UsbKeyboard& usbKeyboard,
//                        const KeyId& modifier,
//                        const KeyId& key)
// {
//     return [&usbKeyboard, modifier, key](const ActionContext& context)
//     {
//         if (context.state != KeyState::kReleased)
//         {
//             usbKeyboard.setModifier(modifier.value());
//             usbKeyboard.setKey(key.value());
//         }
        
//         if (context.state != KeyState::kHeld)
//         {
//             usbKeyboard.markDirty();
//         }
//     };
// }

}
