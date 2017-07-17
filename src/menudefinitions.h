#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

#include "ui/arraydatasource.h"
#include "ui/menu.h"

class StrOStream;
class KeyboardState;

namespace Impl
{

class MacroDataSource : public UI::Menu::DataSource
{
public:
    explicit constexpr MacroDataSource(KeyboardState& keyboardState);

public:
    virtual void getItem(const StrOStream& os,
                         KeyId&            keyId,
                         std::size_t       index) const;

    virtual std::size_t getItemCount() const;

public:
    KeyboardState& mKeyboardState;

private:
    MacroDataSource(const MacroDataSource&) = delete;
    MacroDataSource& operator=(const MacroDataSource&) = delete;
};


class EditMacroDataSource : public UI::Menu::DataSource
{
public:
    explicit constexpr EditMacroDataSource(KeyboardState& keyboardState);

public:
    virtual void getItem(const StrOStream& os,
                         KeyId&            keyId,
                         std::size_t       index) const;

    virtual std::size_t getItemCount() const;

public:
    KeyboardState& mKeyboardState;

private:
    EditMacroDataSource(const EditMacroDataSource&) = delete;
    EditMacroDataSource& operator=(const EditMacroDataSource&) = delete;
};


class LockDataSource : public UI::Menu::DataSource
{
public:
    explicit constexpr LockDataSource(KeyboardState& keyboardState);

public:
    virtual void getItem(const StrOStream& os,
                         KeyId&            keyId,
                         std::size_t       index) const;

    virtual std::size_t getItemCount() const;

public:
    KeyboardState& mKeyboardState;
    
private:
    LockDataSource(const LockDataSource&) = delete;
    LockDataSource& operator=(const LockDataSource&) = delete;
};

class KeyDataSource : public UI::Menu::DataSource
{
public:
    explicit constexpr KeyDataSource(KeyboardState& keyboardState);

public:
    virtual void getItem(const StrOStream& os,
                         KeyId&            keyId,
                         std::size_t       index) const;

    virtual std::size_t getItemCount() const;

public:
    KeyboardState& mKeyboardState;

private:
    KeyDataSource(const KeyDataSource&) = delete;
    KeyDataSource& operator=(const KeyDataSource&) = delete;
};

}

class MenuDefinitions
{
public:
    explicit MenuDefinitions(KeyboardState& keyboardState);

public:
    const UI::Menu::DataSource& getDataSource(int id) const;

private:
    const UI::ArrayDataSource mMainMenuSource;
    const UI::ArrayDataSource mEmptyMenuSource;

    const Impl::MacroDataSource     mMacroDataSource;
    const Impl::EditMacroDataSource mEditMacroDataSource;
    const Impl::LockDataSource      mLockDataSource;
    const Impl::KeyDataSource       mKeyDataSource;

private:
    MenuDefinitions(const MenuDefinitions&) = delete;
    MenuDefinitions& operator=(const MenuDefinitions&) = delete;
};

#endif
