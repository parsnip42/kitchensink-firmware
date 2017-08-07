#include "menudefinitions.h"

#include "keyboardstate.h"
#include "keyid.h"
#include "data/keycodes.h"
#include "screenid.h"

namespace
{

const std::array<MenuScreen::Item, 6> mainMenu = { {
        { StrRef("Macros"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 1) },
        { StrRef("Keys"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 4) },
        { StrRef("Edit Macros"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 2) },
        { StrRef("Multi Keys"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 6) },
        { StrRef("Smart Keys"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 3) },
        { StrRef("System"), StrRef(), KeyId::Screen(ScreenId::Type::kMenu, 5) },
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

MenuScreen::Item createKeyMenuItem(std::size_t index)
{
    MenuScreen::Item item;
    
    auto keyName(KeyCodes::keyName(index + 1));

    if (keyName == "")
    {
        keyName = "Reserved";
    }

    {
        StrOStream os(item.title);

        os.reset();
        os.appendStr(keyName);
    }

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
    , mSystemMenuSource(systemMenu.begin(), systemMenu.end())
    , mEmptyMenuSource(mainMenu.end(), mainMenu.end())
    , mMacroDataSource(keyboardState.macroSet, &createMacroMenuItem)
    , mEditMacroDataSource(keyboardState.macroSet, &createEditMacroMenuItem)
    , mMultiKeyDataSource(keyboardState.multiSet, &createMultiKeyMenuItem)
    , mSmartKeyDataSource(keyboardState.smartKeySet, &createSmartKeyMenuItem)
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
        return mEditMacroDataSource;
    case 3:
        return mSmartKeyDataSource;
    case 4:
        return mKeyDataSource;
    case 5:
        return mSystemMenuSource;
    case 6:
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
        return "Edit Macros";
    case 3:
        return "Smart Keys";
    case 4:
        return "Keys";
    case 5:
        return "System";
    case 6:
        return "Multi Keys";
    default:
        return "";
    }
}
