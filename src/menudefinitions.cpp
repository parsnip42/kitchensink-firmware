#include "menudefinitions.h"

#include "keyboardstate.h"
#include "keyid.h"
#include "data/keycodes.h"

namespace
{

const std::array<MenuScreen::Item, 6> mainMenu = { {
        { StrRef("Macros"), StrRef(), KeyId::Action(KeyId::ActionType::kMenu, 1) },
        { StrRef("Keys"), StrRef(), KeyId::Action(KeyId::ActionType::kMenu, 4) },
        { StrRef("Edit Macros"), StrRef(), KeyId::Action(KeyId::ActionType::kMenu, 2) },
        { StrRef("Multi Keys"), StrRef(), KeyId::Action(KeyId::ActionType::kMenu, 6) },
        { StrRef("Smart Keys"), StrRef(), KeyId::Action(KeyId::ActionType::kMenu, 3) },
        { StrRef("System"), StrRef(), KeyId::Action(KeyId::ActionType::kMenu, 5) },
    } };

const std::array<MenuScreen::Item, 3> systemMenu = { {
        { StrRef("Storage"), StrRef(), KeyId::Action(KeyId::ActionType::kScreen, 0) },
        { StrRef("Benchmark"), StrRef(), KeyId::Action(KeyId::ActionType::kScreen, 1) },
        { StrRef("Bootloader"), StrRef(), KeyId::Action(KeyId::ActionType::kBuiltIn, 0) } 
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
    item.keyId    = KeyId::Action(KeyId::ActionType::kEditMacro, index);
        
    return item;
}

MenuScreen::Item createMultiKeyMenuItem(const Multi& multi, std::size_t index)
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
