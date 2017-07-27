#include "menudefinitions.h"

#include "keyboardstate.h"
#include "keyid.h"
#include "data/keycodes.h"

namespace
{

const UI::ArrayDataSource::Item mainMenuItems[] =
{
    UI::ArrayDataSource::Item("Keys", KeyId::Action(KeyId::ActionType::kMenu, 4)),
    UI::ArrayDataSource::Item("Macros", KeyId::Action(KeyId::ActionType::kMenu, 1)),
    UI::ArrayDataSource::Item("Edit Macros", KeyId::Action(KeyId::ActionType::kMenu, 2)),
    UI::ArrayDataSource::Item("Key Locks", KeyId::Action(KeyId::ActionType::kMenu, 3)),
    UI::ArrayDataSource::Item("System", KeyId::Action(KeyId::ActionType::kMenu, 5)),
    UI::ArrayDataSource::Item("Bootloader", KeyId::Action(KeyId::ActionType::kBuiltIn, 0))
};

const UI::ArrayDataSource::Item systemMenuItems[] =
{
    UI::ArrayDataSource::Item("Storage", KeyId::Action(KeyId::ActionType::kScreen, 0)),
    UI::ArrayDataSource::Item("Benchmark", KeyId::Action(KeyId::ActionType::kScreen, 1))
};

const UI::ArrayDataSource::Item emptyMenuItems[] =
{
    UI::ArrayDataSource::Item("--", KeyId()),
};

}

namespace Impl
{

MacroDataSource::MacroDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void MacroDataSource::getItem(UI::Menu::Item& menuItem,
                              std::size_t     index) const

{
    menuItem.title = mKeyboardState.macroSet[index].name;
    menuItem.shortcut = mKeyboardState.macroSet[index].shortcut;
    menuItem.keyId = KeyId::Macro(index);
}

std::size_t MacroDataSource::getItemCount() const
{
    return mKeyboardState.macroSet.size();
}


EditMacroDataSource::EditMacroDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void EditMacroDataSource::getItem(UI::Menu::Item& menuItem,
                                  std::size_t     index) const
{
    
    menuItem.title = mKeyboardState.macroSet[index].name;
    menuItem.keyId = KeyId::Action(KeyId::ActionType::kEditMacro, index);
}

std::size_t EditMacroDataSource::getItemCount() const
{
    return mKeyboardState.macroSet.size();
}


LockDataSource::LockDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void LockDataSource::getItem(UI::Menu::Item& menuItem,
                             std::size_t     index) const
{
    
    menuItem.title = mKeyboardState.lockSet[index].name;
    menuItem.keyId = KeyId::Lock(KeyId::LockType::kToggle, index);
}

std::size_t LockDataSource::getItemCount() const
{
    return mKeyboardState.lockSet.size();
}


KeyDataSource::KeyDataSource(const KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void KeyDataSource::getItem(UI::Menu::Item& menuItem,
                            std::size_t     index) const
{
    auto keyName(KeyCodes::keyName(index + 1));

    if (keyName == "")
    {
        keyName = "Reserved";
    }

    {
        StrOStream os(menuItem.title);

        os.reset();
        os.appendStr(keyName);
        os.appendStr(" (");
        os.appendInt(index + 1, "0x%2.2x");
        os.appendStr(")");
    }

    {
        StrOStream os(menuItem.shortcut);
        
        os.reset();
        os.appendInt(index + 1, "%2.2x");
    }
    
    menuItem.keyId = KeyId(index + 1);
}

std::size_t KeyDataSource::getItemCount() const
{
    return 255;
}

}

MenuDefinitions::MenuDefinitions(const KeyboardState& keyboardState)
    : mMainMenuSource(mainMenuItems)
    , mSystemMenuSource(systemMenuItems)
    , mEmptyMenuSource(emptyMenuItems)
    , mMacroDataSource(keyboardState)
    , mEditMacroDataSource(keyboardState)
    , mLockDataSource(keyboardState)
    , mKeyDataSource(keyboardState)
{ }

const UI::Menu::DataSource& MenuDefinitions::getDataSource(int id) const
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
        return mLockDataSource;
    case 4:
        return mKeyDataSource;
    case 5:
        return mSystemMenuSource;
    default:
        return mEmptyMenuSource;
    }
}

