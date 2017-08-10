#include "ui/menudefinitions.h"

#include "keyboardstate.h"
#include "keyid.h"
#include "data/keycodes.h"
#include "screenid.h"

namespace
{

const std::array<MenuScreen::Item, 6> mainMenu = { {
        { StrRef("Macros"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 1) },
        { StrRef("Secure Macros"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 2) },
        { StrRef("Keys"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 3) },
        { StrRef("Layers"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 4) },
        { StrRef("Configuration"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 5) },
        { StrRef("System"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 6) },
    } };

const std::array<MenuScreen::Item, 5> configMenu = { {
        { StrRef("Layout Configuration"), StrRef(), KeyId::Screen(ScreenId::Type::kScreen, 2) },
        { StrRef("Edit Macros"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 10) },
        { StrRef("Edit Secure Macros"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 11) },
        { StrRef("Edit Multi Keys"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 12) },
        { StrRef("Edit Smart Keys"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 13) },
    } };

const std::array<MenuScreen::Item, 3> systemMenu = { {
        { StrRef("Storage"), StrRef(), KeyId::Screen(ScreenId::Type::kScreen, 0) },
        { StrRef("Benchmark"), StrRef(), KeyId::Screen(ScreenId::Type::kScreen, 1) },
        { StrRef("Bootloader"), StrRef(), KeyId::Action(0) } 
    } };


MenuScreen::Item createMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.keyId    = KeyId::Macro(index);
        
    return item;
}

MenuScreen::Item createEditMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.keyId    = KeyId::Screen(ScreenId::Type::kEditMacro, index);
        
    return item;
}

MenuScreen::Item createSMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.keyId    = KeyId::SMacro(index);
        
    return item;
}

MenuScreen::Item createEditSMacroMenuItem(const Macro& macro, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title    = macro.name;
    item.shortcut = macro.shortcut;
    item.keyId    = KeyId::Screen(ScreenId::Type::kEditSMacro, index);
        
    return item;
}

MenuScreen::Item createMultiKeyMenuItem(const MultiKey& multi, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title = multi.name;
    item.keyId = KeyId::Multi(index);
        
    return item;
}

MenuScreen::Item createSmartKeyMenuItem(const SmartKey& smart, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title = smart.name;
    item.keyId = KeyId::Smart(index);
        
    return item;
}

MenuScreen::Item createLayerMenuItem(const Layer& layer, std::size_t index)
{
    MenuScreen::Item item;
        
    item.title = layer.name;
    item.keyId = KeyId();
        
    return item;
}

MenuScreen::Item createKeyMenuItem(std::size_t index)
{
    MenuScreen::Item item;
    
    auto keyName(KeyCodes::keyName(index + 1));

    if (keyName == "")
    {
        keyName = "Reserved";
    }

    item.title = keyName;

    {
        StrOStream os(item.shortcut);
        
        os.reset();
        os.appendStr("0x");
        os.appendInt(index + 1, "%2.2x");
    }
    
    item.keyId = KeyId(index + 1);

    return item;
}

}

MenuDefinitions::MenuDefinitions(const KeyboardState& keyboardState)
    : mMainMenuSource(mainMenu.begin(), mainMenu.end())
    , mConfigMenuSource(configMenu.begin(), configMenu.end())
    , mSystemMenuSource(systemMenu.begin(), systemMenu.end())
    , mEmptyMenuSource(mainMenu.end(), mainMenu.end())
    , mMacroDataSource(keyboardState.macroSet, &createMacroMenuItem)
    , mEditMacroDataSource(keyboardState.macroSet, &createEditMacroMenuItem)
    , mSMacroDataSource(keyboardState.secureMacroSet, &createSMacroMenuItem)
    , mEditSMacroDataSource(keyboardState.secureMacroSet, &createEditSMacroMenuItem)
    , mMultiKeyDataSource(keyboardState.multiSet, &createMultiKeyMenuItem)
    , mSmartKeyDataSource(keyboardState.smartKeySet, &createSmartKeyMenuItem)
    , mLayerDataSource(keyboardState.layerStack, &createLayerMenuItem)
    , mKeyDataSource(254, &createKeyMenuItem)
{ }

const MenuScreen::DataSource& MenuDefinitions::getDataSource(int id) const
{
    switch (id)
    {
    case 0:
        return mMainMenuSource;
        
    case 1:
        return mMacroDataSource;

    case 2:
        return mSMacroDataSource;
        
    case 3:
        return mKeyDataSource;

    case 4:
        return mLayerDataSource;

    case 5:
        return mConfigMenuSource;

    case 6:
        return mSystemMenuSource;

    case 10:
        return mEditMacroDataSource;

    case 11:
        return mEditSMacroDataSource;

    case 12:
        return mSmartKeyDataSource;
        
    case 13:
        return mMultiKeyDataSource;
        
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
        return "Macros";
        
    case 2:
        return "Secure Macros";
        
    case 3:
        return "Keys";
        
    case 4:
        return "Layers";

    case 5:
        return "Configuration";
        
    case 6:
        return "System";

    case 10:
        return "Macros";
        
    case 11:
        return "Secure Macros";

    case 12:
        return "Smart Keys";
        
    case 13:
        return "Multi Keys";

    default:
        return "";
    }
}
