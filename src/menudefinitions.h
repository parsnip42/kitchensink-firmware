#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

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
};

#endif
