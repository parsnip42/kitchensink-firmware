#include "menudefinitions.h"

#include "keyboardstate.h"
#include "keyid.h"
#include "keycodes.h"

namespace
{

const UI::Menu::Item mainMenuItems[] =
{
    UI::Menu::Item("Keys", KeyId::Action(KeyId::ActionType::kMenu, 4)),
    UI::Menu::Item("Macros", KeyId::Action(KeyId::ActionType::kMenu, 1)),
    UI::Menu::Item("Edit Macros", KeyId::Action(KeyId::ActionType::kMenu, 2)),
    UI::Menu::Item("Key Locks", KeyId::Action(KeyId::ActionType::kMenu, 3)),
    UI::Menu::Item("System", KeyId::Action(KeyId::ActionType::kBuiltIn, 1)),
    UI::Menu::Item("Bootloader", KeyId::Action(KeyId::ActionType::kBuiltIn, 0))
};

const UI::Menu::Item emptyMenuItems[] =
{
    UI::Menu::Item("--", KeyId()),
};

}

namespace Impl
{

constexpr MacroDataSource::MacroDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

UI::Menu::Item MacroDataSource::getItem(std::size_t index) const
{
    return UI::Menu::Item(mKeyboardState.macroSet[index].data.name,
                          KeyId::Macro(index));
}

std::size_t MacroDataSource::getItemCount() const
{
    return mKeyboardState.macroSet.size();
}


constexpr EditMacroDataSource::EditMacroDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

UI::Menu::Item EditMacroDataSource::getItem(std::size_t index) const
{
    return UI::Menu::Item(mKeyboardState.macroSet[index].data.name,
                          KeyId::Action(KeyId::ActionType::kEditMacro, index));
}

std::size_t EditMacroDataSource::getItemCount() const
{
    return mKeyboardState.macroSet.size();
}


constexpr LockDataSource::LockDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

UI::Menu::Item LockDataSource::getItem(std::size_t index) const
{
    return UI::Menu::Item(mKeyboardState.lockSet[index].name,
                          KeyId::Lock(KeyId::LockType::kToggle, index));
}

std::size_t LockDataSource::getItemCount() const
{
    return mKeyboardState.lockSet.size();
}


constexpr KeyDataSource::KeyDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

UI::Menu::Item KeyDataSource::getItem(std::size_t index) const
{
    return UI::Menu::Item(KeyCodes::Names[index], KeyId(index));
}

std::size_t KeyDataSource::getItemCount() const
{
    return KeyCodes::NameCount;
}

}

MenuDefinitions::MenuDefinitions(KeyboardState& keyboardState)
    : mMainMenuSource(mainMenuItems)
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
    default:
        return mEmptyMenuSource;
    }
}

