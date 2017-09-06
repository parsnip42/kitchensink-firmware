#ifndef INCLUDED_MENUDEFINITIONS_H
#define INCLUDED_MENUDEFINITIONS_H

#include "ui/menuwidget.h"
#include "types/arrayobjectsource.h"
#include "types/mappedobjectsource.h"
#include "types/generatedobjectsource.h"
#include "macroset.h"
#include "multikeyset.h"
#include "smartkeyset.h"
#include "layerstack.h"
#include "data/keycodes.h"

class KeyboardState;

class MenuDefinitions
{
public:
    explicit MenuDefinitions(const KeyboardState& keyboardState);

public:
    StrRef getTitle(int id) const;
    const MenuWidget::DataSource& getDataSource(int id) const;

private:
    const ArrayObjectSource<MenuWidget::Item> mMainMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mConfigMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mSystemMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mEventMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mEmptyMenuSource;

    const GeneratedObjectSource<MenuWidget::Item>           mKeyDataSource;
    const MappedObjectSource<MenuWidget::Item, LayerStack>  mLayerDataSource;
    const MappedObjectSource<MenuWidget::Item, MacroSet>    mMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, MacroSet>    mSMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, MultiKeySet> mMultiKeyDataSource;
    const MappedObjectSource<MenuWidget::Item, SmartKeySet> mSmartKeyDataSource;
    
    const MappedObjectSource<MenuWidget::Item, LayerStack>  mEditLayerDataSource;
    const MappedObjectSource<MenuWidget::Item, MacroSet>    mEditMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, MacroSet>    mEditSMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, MultiKeySet> mEditMultiKeyDataSource;
    const MappedObjectSource<MenuWidget::Item, SmartKeySet> mEditSmartKeyDataSource;

private:
    MenuDefinitions(const MenuDefinitions&) = delete;
    MenuDefinitions& operator=(const MenuDefinitions&) = delete;
};

#endif
