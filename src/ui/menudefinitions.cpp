#include "ui/menudefinitions.h"

#include "types/stroutstream.h"
#include "keyboardstate.h"
#include "data/keycode.h"
#include "data/keycodeutil.h"
#include "event/event.h"
#include "event/actionevent.h"
#include "event/keyevent.h"
#include "event/screenevent.h"
#include "event/macroevent.h"
#include "event/multievent.h"
#include "event/smartevent.h"
#include "event/layerevent.h"

namespace
{

const std::array<MenuWidget::Item, 5> mainMenu = { {
        { StrRef("Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 12) },
        { StrRef("Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 13) },
        { StrRef("Keys"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 10) },
        { StrRef("Configuration"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 1) },
        { StrRef("System"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 2) },
    } };

const std::array<MenuWidget::Item, 6> configMenu = { {
        { StrRef("Settings"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, 0) },
        { StrRef("Edit Layers"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 20) },
        { StrRef("Edit Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 21) },
        { StrRef("Edit Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 22) },
        { StrRef("Edit Multi Keys"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 23) },
        { StrRef("Edit Smart Keys"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 24) },
    } };

const std::array<MenuWidget::Item, 4> systemMenu = { {
        { StrRef("Status"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, 1) },
        { StrRef("Cryptography"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, 2) },
        { StrRef("Event Stream"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, 3) },
        // { StrRef("Switch Analysis"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, 4) },
        { StrRef("Bootloader"), StrRef(), ActionEvent::create(0) } 
    } };

const std::array<MenuWidget::Item, 6> eventMenu = { {
        { StrRef("Keys"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 10) },
        { StrRef("Layers"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 11) },
        { StrRef("Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 12) },
        { StrRef("Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 13) },
        { StrRef("Multi Keys"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 14) },
        { StrRef("Smart Keys"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, 15) }
    } };

MenuWidget::Item createKeyMenuItem(std::size_t index)
{
    MenuWidget::Item item;
    
    auto keyName(KeyCodeUtil::keyName(static_cast<KeyCode>(index)));

    if (keyName == "")
    {
        keyName = "Reserved";
    }

    item.title = keyName;

    if (index != 0)
    {
        StrOutStream os(item.shortcut);
        
        os.reset();
        os.appendStr("0x");
        os.appendInt(index, "%2.2x");
    }
    
    item.event = KeyEvent::create(static_cast<KeyCode>(index));

    return item;
}

MenuWidget::Item createLayerMenuItem(const Layer& layer, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title = layer.name;
    item.event = LayerEvent::create(index);
        
    return item;
}

MenuWidget::Item createMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.event    = MacroEvent::create(MacroEvent::Type::kDefault, index);
        
    return item;
}

MenuWidget::Item createSMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.event    = MacroEvent::create(MacroEvent::Type::kSecure, index);
        
    return item;
}

MenuWidget::Item createMultiKeyMenuItem(const MultiKey& multi, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title = multi.name;
    item.event = MultiEvent::create(index);

    return item;
}

MenuWidget::Item createSmartKeyMenuItem(const SmartKey& smart, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title = smart.name;
    item.event = SmartEvent::create(index);
        
    return item;
}

MenuWidget::Item createEditLayerMenuItem(const Layer& layer, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title = layer.name;
    item.event = ScreenEvent::create(ScreenEvent::Type::kEditLayer, index);
        
    return item;
}

MenuWidget::Item createEditMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.event    = ScreenEvent::create(ScreenEvent::Type::kEditMacro, index);
        
    return item;
}

MenuWidget::Item createEditSMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.event    = ScreenEvent::create(ScreenEvent::Type::kEditSMacro, index);
        
    return item;
}

MenuWidget::Item createEditMultiKeyMenuItem(const MultiKey& multi, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title = multi.name;
    item.event = ScreenEvent::create(ScreenEvent::Type::kEditMulti, index);

    return item;
}

MenuWidget::Item createEditSmartKeyMenuItem(const SmartKey& smart, std::size_t index)
{
    MenuWidget::Item item;
        
    item.title = smart.name;
    item.event = ScreenEvent::create(ScreenEvent::Type::kEditSmart, index);
        
    return item;
}

}

MenuDefinitions::MenuDefinitions(const KeyboardState& keyboardState)
    : mMainMenuSource(mainMenu.begin(), mainMenu.end())
    , mConfigMenuSource(configMenu.begin(), configMenu.end())
    , mSystemMenuSource(systemMenu.begin(), systemMenu.end())
    , mEventMenuSource(eventMenu.begin(), eventMenu.end())
    , mEmptyMenuSource(mainMenu.end(), mainMenu.end())
      
    , mKeyDataSource(255, &createKeyMenuItem)
    , mLayerDataSource(keyboardState.layerStack, &createLayerMenuItem)
    , mMacroDataSource(keyboardState.macroSet, &createMacroMenuItem)
    , mSMacroDataSource(keyboardState.secureMacroSet, &createSMacroMenuItem)
    , mMultiKeyDataSource(keyboardState.multiKeySet, &createMultiKeyMenuItem)
    , mSmartKeyDataSource(keyboardState.smartKeySet, &createSmartKeyMenuItem)

    , mEditLayerDataSource(keyboardState.layerStack, &createEditLayerMenuItem)
    , mEditMacroDataSource(keyboardState.macroSet, &createEditMacroMenuItem)
    , mEditSMacroDataSource(keyboardState.secureMacroSet, &createEditSMacroMenuItem)
    , mEditMultiKeyDataSource(keyboardState.multiKeySet, &createEditMultiKeyMenuItem)
    , mEditSmartKeyDataSource(keyboardState.smartKeySet, &createEditSmartKeyMenuItem)
{ }

const MenuWidget::DataSource& MenuDefinitions::getDataSource(int id) const
{
    switch (id)
    {
    case 0:
        return mMainMenuSource;

    case 1:
        return mConfigMenuSource;

    case 2:
        return mSystemMenuSource;

    case 3:
        return mEventMenuSource;


    case 10:
        return mKeyDataSource;

    case 11:
        return mLayerDataSource;

    case 12:
        return mMacroDataSource;

    case 13:
        return mSMacroDataSource;
        
    case 14:
        return mMultiKeyDataSource;
        
    case 15:
        return mSmartKeyDataSource;


    case 20:
        return mEditLayerDataSource;

    case 21:
        return mEditMacroDataSource;

    case 22:
        return mEditSMacroDataSource;

    case 23:
        return mEditMultiKeyDataSource;
        
    case 24:
        return mEditSmartKeyDataSource;

    default:
        return mEmptyMenuSource;
    }
}

StrRef MenuDefinitions::getTitle(int id) const
{
    switch (id)
    {
    case 0:
        return "Main Menu";
        
    case 1:
        return "Configuration";
        
    case 2:
        return "System";

    case 3:
        return "Events";


    case 10:
        return "Keys";
        
    case 11:
        return "Layers";

    case 12:
        return "Macros";
        
    case 13:
        return "Secure Macros";
                
    case 14:
        return "Multi Keys";
        
    case 15:
        return "Smart Keys";

    case 20:
        return "Edit Layers";

    case 21:
        return "Edit Macros";
        
    case 22:
        return "Edit Secure Macros";
                               
    case 23:
        return "Edit Multi Keys";
        
    case 24:
        return "Edit Smart Keys";

        
    default:
        return "";
    }
}
