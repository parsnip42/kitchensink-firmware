#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

#include "ui/menuscreen.h"
#include "types/arrayobjectsource.h"
#include "types/mappedobjectsource.h"
#include "types/generatedobjectsource.h"
#include "macroset.h"
#include "multiset.h"
#include "smartkeyset.h"
#include "data/keycodes.h"

class StrOStream;
class KeyboardState;

class MenuDefinitions
{
public:
    explicit MenuDefinitions(const KeyboardState& keyboardState);

public:
    StrRef getTitle(int id) const;
    const MenuScreen::DataSource& getDataSource(int id) const;

private:
    const ArrayObjectSource<MenuScreen::Item> mMainMenuSource;
    const ArrayObjectSource<MenuScreen::Item> mSystemMenuSource;
    const ArrayObjectSource<MenuScreen::Item> mEmptyMenuSource;

    const MappedObjectSource<MenuScreen::Item, MacroSet>    mMacroDataSource;
    const MappedObjectSource<MenuScreen::Item, MacroSet>    mEditMacroDataSource;
    const MappedObjectSource<MenuScreen::Item, MultiSet>    mMultiKeyDataSource;
    const MappedObjectSource<MenuScreen::Item, SmartKeySet> mSmartKeyDataSource;
    const GeneratedObjectSource<MenuScreen::Item>           mKeyDataSource;

private:
    MenuDefinitions(const MenuDefinitions&) = delete;
    MenuDefinitions& operator=(const MenuDefinitions&) = delete;
};

#endif
