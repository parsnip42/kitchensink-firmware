#ifndef INCLUDED_MENUSCREEN_H
#define INCLUDED_MENUSCREEN_H

#include "keyeventstage.h"
#include "keyid.h"
#include "types/mappedobjectsource.h"
#include "types/objectsource.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/menuwidget.h"
#include "ui/hsplitwidget.h"
#include "ui/menutitlewidget.h"
#include "ui/textentrywidget.h"

class EventManager;
class Surface;

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
    MenuScreen(const StrRef&     title,
               const DataSource& dataSource,
               Surface&          surface,
               EventManager&     eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    void poll();

private:
    StrRef            mTitle;
    Surface&          mSurface;
    EventManager&     mEventManager;
    const DataSource& mDataSource;
    MenuDataSource    mMenuDataSource;
    MenuWidget        mMenuWidget;
    MenuTitleWidget   mTitleWidget;
    HSplitWidget      mHSplit;
    bool              mQuit;
};

#endif
