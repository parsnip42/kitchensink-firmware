#ifndef INCLUDED_MENUSCREEN_H
#define INCLUDED_MENUSCREEN_H

#include "keyeventstage.h"
#include "keyid.h"
#include "types/mappedobjectsource.h"
#include "types/objectsource.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/menuwidget.h"

class Timer;
class ScreenStack;
class Widget;

class MenuScreen : public KeyEventStage
{
public:
    class Item
    {
    public:
        StrBuf<24> title;
        StrBuf<12> shortcut;
        KeyId      keyId;
    };
    
public:
    typedef ObjectSource<Item> DataSource;
    
private:
    typedef MappedObjectSource<MenuItemWidget, DataSource> MenuDataSource;
        
public:
    MenuScreen(const DataSource& dataSource,
               ScreenStack&      screenStack,
               KeyEventStage&    next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    Widget& rootWidget();
    
private:
    const DataSource& mDataSource;
    MenuDataSource    mMenuDataSource;
    MenuWidget        mMenuWidget;
    ScreenStack&      mScreenStack;
    KeyEventStage&    mNext;
};

#endif
