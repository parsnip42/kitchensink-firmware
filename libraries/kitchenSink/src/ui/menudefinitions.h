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

class KeyboardState;

class MenuDefinitions
{
public:
    enum
    {
        kMainMenu         = 0,
        kConfiguration    = 1,
        kUtils            = 2,
        kSystem           = 3,
        kEvents           = 4,
        
        kKeys             = 10,
        kLayers           = 11,
        kMacros           = 12,
        kSecureMacros     = 13,
        kMultiKeys        = 14,
        kSmartKeys        = 15,
        
        kEditLayers       = 20,
        kEditMacros       = 21,
        kEditSecureMacros = 22,
        kEditMultiKeys    = 23,
        kEditSmartKeys    = 24
    };

    typedef uint8_t MenuId;
    
public:
    explicit MenuDefinitions(const KeyboardState& keyboardState);

public:
    StrRef getTitle(MenuId id) const;
    const MenuWidget::DataSource& getDataSource(MenuId id) const;

private:
    const ArrayObjectSource<MenuWidget::Item> mMainMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mConfigMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mUtilsMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mSystemMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mEventMenuSource;
    const ArrayObjectSource<MenuWidget::Item> mEmptyMenuSource;

    const GeneratedObjectSource<MenuWidget::Item>              mKeyDataSource;
    const MappedObjectSource<MenuWidget::Item, LayerStack>     mLayerDataSource;
    const MappedObjectSource<MenuWidget::Item, MacroSet>       mMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, SecureMacroSet> mSMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, MultiKeySet>    mMultiKeyDataSource;
    const MappedObjectSource<MenuWidget::Item, SmartKeySet>    mSmartKeyDataSource;
    
    const MappedObjectSource<MenuWidget::Item, LayerStack>     mEditLayerDataSource;
    const MappedObjectSource<MenuWidget::Item, MacroSet>       mEditMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, SecureMacroSet> mEditSMacroDataSource;
    const MappedObjectSource<MenuWidget::Item, MultiKeySet>    mEditMultiKeyDataSource;
    const MappedObjectSource<MenuWidget::Item, SmartKeySet>    mEditSmartKeyDataSource;

private:
    MenuDefinitions(const MenuDefinitions&) = delete;
    MenuDefinitions& operator=(const MenuDefinitions&) = delete;
};

#endif
