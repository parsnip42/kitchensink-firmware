#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

#include "ui/arraydatasource.h"
#include "ui/menu.h"

class KeyboardState;

namespace Impl
{

class MacroDataSource : public UI::Menu::DataSource
{
public:
    explicit constexpr MacroDataSource(KeyboardState& keyboardState);

public:
    virtual UI::Menu::Item getItem(std::size_t index) const;
    virtual std::size_t getItemCount() const;

public:
    KeyboardState& mKeyboardState;
};


class EditMacroDataSource : public UI::Menu::DataSource
{
public:
    explicit constexpr EditMacroDataSource(KeyboardState& keyboardState);

public:
    virtual UI::Menu::Item getItem(std::size_t index) const;
    virtual std::size_t getItemCount() const;

public:
    KeyboardState& mKeyboardState;
};

}

class MenuDefinitions
{
public:
    explicit MenuDefinitions(KeyboardState& keyboardState);

public:
    const UI::Menu::DataSource& getDataSource(int id) const;

private:
    KeyboardState& mKeyboardState;

    const UI::ArrayDataSource mMainMenuSource;
    const UI::ArrayDataSource mConfigMenuSource;
    const UI::ArrayDataSource mEmptyMenuSource;

    const Impl::MacroDataSource     mMacroDataSource;
    const Impl::EditMacroDataSource mEditMacroDataSource;

private:
    MenuDefinitions(const MenuDefinitions&);
    MenuDefinitions& operator=(const MenuDefinitions&);
};

#endif
