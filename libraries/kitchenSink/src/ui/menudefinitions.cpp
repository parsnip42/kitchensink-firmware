#include "ui/menudefinitions.h"

#include "data/keycode.h"
#include "data/keycodeutil.h"
#include "event/actionevent.h"
#include "event/event.h"
#include "event/keyevent.h"
#include "event/layerevent.h"
#include "event/macroevent.h"
#include "event/multievent.h"
#include "event/screenevent.h"
#include "event/smartevent.h"
#include "keyboardstate.h"
#include "types/stroutstream.h"

namespace
{

const std::array<MenuWidget::Item, 6> mainMenu = { {
        { StrRef("Macros"),        StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kMacros) },
        { StrRef("Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kSecureMacros) },
        { StrRef("Configuration"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kConfiguration) },
        { StrRef("Utilities"),     StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kUtils) },
        { StrRef("Actions"),       StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kEvents) },
        { StrRef("System"),        StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kSystem) },
    } };

const std::array<MenuWidget::Item, 6> configMenu = { {
        { StrRef("Global Settings"),    StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kGlobalSettings) },
        { StrRef("Edit Layers"),        StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kEditLayers) },
        { StrRef("Edit Macros"),        StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kEditMacros) },
        { StrRef("Edit Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kEditSecureMacros) },
        { StrRef("Edit Multi Keys"),    StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kEditMultiKeys) },
        { StrRef("Edit Smart Keys"),    StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kEditSmartKeys) },
    } };

const std::array<MenuWidget::Item, 3> utilsMenu = { {
        { StrRef("Lock Secure Macros"),   StrRef(), ActionEvent::create(ActionEvent::Type::kLockSecureMacros) },
        { StrRef("Unlock Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kMacroUnlock) },
        { StrRef("Setup Secure Macros"),  StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kInitSecureMacros) }
    } };

const std::array<MenuWidget::Item, 5> systemMenu = { {
        { StrRef("Status"),            StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kStatus) },
        { StrRef("Cryptography"),      StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kCryptography) },
        { StrRef("Dump Entropy Pool"), StrRef(), ActionEvent::create(ActionEvent::Type::kDumpEntropyPool) },
        { StrRef("Event Stream"),      StrRef(), ScreenEvent::create(ScreenEvent::Type::kScreen, ScreenEvent::kEventStream) },
        { StrRef("Bootloader"),        StrRef(), ActionEvent::create(ActionEvent::Type::kBootloader) } 
    } };

const std::array<MenuWidget::Item, 6> eventMenu = { {
        { StrRef("Keys"),          StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kKeys) },
        { StrRef("Layers"),        StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kLayers) },
        { StrRef("Macros"),        StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kMacros) },
        { StrRef("Secure Macros"), StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kSecureMacros) },
        { StrRef("Multi Keys"),    StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kMultiKeys) },
        { StrRef("Smart Keys"),    StrRef(), ScreenEvent::create(ScreenEvent::Type::kMenu, MenuDefinitions::kSmartKeys) }
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
    , mUtilsMenuSource(utilsMenu.begin(), utilsMenu.end())
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

const MenuWidget::DataSource& MenuDefinitions::getDataSource(MenuId id) const
{
    switch (id)
    {
    case kMainMenu:
        return mMainMenuSource;

    case kConfiguration:
        return mConfigMenuSource;

    case kUtils:
        return mUtilsMenuSource;

    case kSystem:
        return mSystemMenuSource;

    case kEvents:
        return mEventMenuSource;


    case kKeys:
        return mKeyDataSource;

    case kLayers:
        return mLayerDataSource;

    case kMacros:
        return mMacroDataSource;

    case kSecureMacros:
        return mSMacroDataSource;
        
    case kMultiKeys:
        return mMultiKeyDataSource;
        
    case kSmartKeys:
        return mSmartKeyDataSource;


    case kEditLayers:
        return mEditLayerDataSource;

    case kEditMacros:
        return mEditMacroDataSource;

    case kEditSecureMacros:
        return mEditSMacroDataSource;

    case kEditMultiKeys:
        return mEditMultiKeyDataSource;
        
    case kEditSmartKeys:
        return mEditSmartKeyDataSource;

    default:
        return mEmptyMenuSource;
    }
}

StrRef MenuDefinitions::getTitle(MenuId id) const
{
    switch (id)
    {
    case kMainMenu:
        return "Main Menu";
        
    case kConfiguration:
        return "Configuration";

    case kUtils:
        return "Utilities";
        
    case kSystem:
        return "System";

    case kEvents:
        return "Events";


    case kKeys:
        return "Keys";
        
    case kLayers:
        return "Layers";

    case kMacros:
        return "Macros";
        
    case kSecureMacros:
        return "Secure Macros";
                
    case kMultiKeys:
        return "Multi Keys";
        
    case kSmartKeys:
        return "Smart Keys";

    case kEditLayers:
        return "Edit Layers";

    case kEditMacros:
        return "Edit Macros";
        
    case kEditSecureMacros:
        return "Edit Secure Macros";
                               
    case kEditMultiKeys:
        return "Edit Multi Keys";
        
    case kEditSmartKeys:
        return "Edit Smart Keys";

        
    default:
        return "";
    }
}
