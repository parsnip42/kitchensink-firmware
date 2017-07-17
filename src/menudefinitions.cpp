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
    UI::ArrayDataSource::Item("System", KeyId::Action(KeyId::ActionType::kBuiltIn, 1)),
    UI::ArrayDataSource::Item("Bootloader", KeyId::Action(KeyId::ActionType::kBuiltIn, 0))
};

const UI::ArrayDataSource::Item emptyMenuItems[] =
{
    UI::ArrayDataSource::Item("--", KeyId()),
};

}

namespace Impl
{

constexpr MacroDataSource::MacroDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void MacroDataSource::getItem(const StrOStream& os,
                              KeyId&            keyId,
                              std::size_t       index) const

{
    os.appendStr(mKeyboardState.macroSet[index].name());
    keyId = KeyId::Macro(index);
}

std::size_t MacroDataSource::getItemCount() const
{
    return mKeyboardState.macroSet.size();
}


constexpr EditMacroDataSource::EditMacroDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void EditMacroDataSource::getItem(const StrOStream& os,
                                  KeyId&            keyId,
                                  std::size_t       index) const
{
    
    os.appendStr(mKeyboardState.macroSet[index].name());
    keyId = KeyId::Action(KeyId::ActionType::kEditMacro, index);
}

std::size_t EditMacroDataSource::getItemCount() const
{
    return mKeyboardState.macroSet.size();
}


constexpr LockDataSource::LockDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void LockDataSource::getItem(const StrOStream& os,
                             KeyId&            keyId,
                             std::size_t       index) const
{
    
    os.appendStr(mKeyboardState.lockSet[index].name);
    keyId = KeyId::Lock(KeyId::LockType::kToggle, index);
}

std::size_t LockDataSource::getItemCount() const
{
    return mKeyboardState.lockSet.size();
}


constexpr KeyDataSource::KeyDataSource(KeyboardState& keyboardState)
    : mKeyboardState(keyboardState)
{ }

void KeyDataSource::getItem(const StrOStream& os,
                            KeyId&            keyId,
                            std::size_t       index) const
{
    auto keyName(KeyCodes::keyName(index));

    if (keyName == "")
    {
        keyName = "Reserved";
    }
    
    os.appendInt(index, "0x%2.2x");
    os.appendStr(" : ");
    os.appendStr(keyName);
    
    keyId = KeyId(index);
}

std::size_t KeyDataSource::getItemCount() const
{
    return 255;
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

