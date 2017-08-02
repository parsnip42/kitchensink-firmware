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

}

namespace Impl
{

MacroDataSource::MacroDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

MenuScreen::Item MacroDataSource::operator[](std::size_t index) const
{
    MenuScreen::Item item;
    
    item.title = mKeyboardState.macroSet[index].name;
    item.shortcut = mKeyboardState.macroSet[index].shortcut;
    item.keyId = KeyId::Macro(index);

    return item;
}

std::size_t MacroDataSource::size() const
{
    return mKeyboardState.macroSet.size();
}


EditMacroDataSource::EditMacroDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

MenuScreen::Item EditMacroDataSource::operator[](std::size_t index) const
{
    MenuScreen::Item item;    

    item.title = mKeyboardState.macroSet[index].name;
    item.keyId = KeyId::Action(KeyId::ActionType::kEditMacro, index);

    return item;
}

std::size_t EditMacroDataSource::size() const
{
    return mKeyboardState.macroSet.size();
}

MultiKeyDataSource::MultiKeyDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

MenuScreen::Item MultiKeyDataSource::operator[](std::size_t index) const
{
    MenuScreen::Item item;
   
    item.title = mKeyboardState.multiSet[index].name;
    item.keyId = KeyId::Multi(index);

    return item;
}

std::size_t MultiKeyDataSource::size() const
{
    return mKeyboardState.multiSet.size();
}

SmartKeyDataSource::SmartKeyDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

MenuScreen::Item SmartKeyDataSource::operator[](std::size_t index) const
{
    MenuScreen::Item item;

    item.title = mKeyboardState.smartKeySet[index].name;
    item.keyId = KeyId::Smart(index);

    return item;
}

std::size_t SmartKeyDataSource::size() const
{
    return mKeyboardState.smartKeySet.size();
}

KeyDataSource::KeyDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

MenuScreen::Item KeyDataSource::operator[](std::size_t index) const
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

std::size_t KeyDataSource::size() const
{
    return 255;
}

}

MenuDefinitions::MenuDefinitions(const KeyboardState& keyboardState)
    : mMainMenuSource(mainMenu.begin(), mainMenu.end())
    , mSystemMenuSource(systemMenu.begin(), systemMenu.end())
    , mEmptyMenuSource(mainMenu.end(), mainMenu.end())
    , mMacroDataSource(keyboardState)
    , mEditMacroDataSource(keyboardState)
    , mMultiKeyDataSource(keyboardState)
    , mSmartKeyDataSource(keyboardState)
    , mKeyDataSource(keyboardState)
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
