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
    explicit MacroDataSource(const KeyboardState& keyboardState);

public:
    virtual void getItem(UI::Menu::Item& menuItem,
                         std::size_t     index) const;

    virtual std::size_t getItemCount() const;

public:
    const KeyboardState& mKeyboardState;

private:
    MacroDataSource(const MacroDataSource&) = delete;
    MacroDataSource& operator=(const MacroDataSource&) = delete;
};


class EditMacroDataSource : public UI::Menu::DataSource
{
public:
    explicit EditMacroDataSource(const KeyboardState& keyboardState);

public:
    virtual void getItem(UI::Menu::Item& menuItem,
                         std::size_t     index) const;

    virtual std::size_t getItemCount() const;

public:
    const KeyboardState& mKeyboardState;

private:
    EditMacroDataSource(const EditMacroDataSource&) = delete;
    EditMacroDataSource& operator=(const EditMacroDataSource&) = delete;
};


class LockDataSource : public UI::Menu::DataSource
{
public:
    explicit LockDataSource(const KeyboardState& keyboardState);

public:
    virtual void getItem(UI::Menu::Item& menuItem,
                         std::size_t     index) const;

    virtual std::size_t getItemCount() const;

public:
    const KeyboardState& mKeyboardState;
    
private:
    LockDataSource(const LockDataSource&) = delete;
    LockDataSource& operator=(const LockDataSource&) = delete;
};

class KeyDataSource : public UI::Menu::DataSource
{
public:
    explicit KeyDataSource(const KeyboardState& keyboardState);

public:
    virtual void getItem(UI::Menu::Item& menuItem,
                         std::size_t     index) const;

    virtual std::size_t getItemCount() const;

public:
    const KeyboardState& mKeyboardState;

private:
    KeyDataSource(const KeyDataSource&) = delete;
    KeyDataSource& operator=(const KeyDataSource&) = delete;
};

}

class MenuDefinitions
{
public:
    explicit MenuDefinitions(const KeyboardState& keyboardState);

public:
    const UI::Menu::DataSource& getDataSource(int id) const;

private:
    const UI::ArrayDataSource mMainMenuSource;
    const UI::ArrayDataSource mSystemMenuSource;
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
