#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

#include "ui/arraydatasource.h"
#include "ui/menu.h"

class KeyboardState;

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

private:
    MenuDefinitions(const MenuDefinitions&);
    MenuDefinitions& operator=(const MenuDefinitions&);
};

#endif
