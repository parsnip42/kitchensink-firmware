#include "actions.h"
#include "actioncontext.h"
#include "keyid.h"
#include "kskeyboard.h"
#include "usbkeyboard.h"

namespace Actions
{

ActionFunc modifierKey(UsbKeyboard& usbKeyboard,
                       const KeyId& modifier,
                       const KeyId& key)
{
    return [&usbKeyboard, modifier, key](const ActionContext& context)
    {
        // if (context.state != KeyState::kReleased)
        // {
        //     usbKeyboard.setModifier(modifier.value());
        //     usbKeyboard.setKey(key.value());
        // }
        
        // if (context.state != KeyState::kHeld)
        // {
        //     usbKeyboard.markDirty();
        // }
    };
}

}
