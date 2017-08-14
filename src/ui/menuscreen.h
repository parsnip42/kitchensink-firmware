#ifndef INCLUDED_MENUSCREEN_H
#define INCLUDED_MENUSCREEN_H

#include "eventstage.h"
#include "event/event.h"
#include "types/mappedobjectsource.h"
#include "types/objectsource.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/menuwidget.h"

class Timer;
class ScreenStack;
class Widget;

class MenuScreen : public EventStage
{
public:
    class Item
    {
    public:
        StrBuf<24> title;
        StrBuf<12> shortcut;
        Event      event;
    };
    
public:
    typedef ObjectSource<Item> DataSource;
    
private:
    typedef MappedObjectSource<MenuItemWidget, DataSource> MenuDataSource;
        
public:
    MenuScreen(const DataSource& dataSource,
               ScreenStack&      screenStack,
               EventStage&       next);

public:
    virtual void processEvent(const Event& event) override;
    
    Widget& rootWidget();
    
private:
    const DataSource& mDataSource;
    MenuDataSource    mMenuDataSource;
    MenuWidget        mMenuWidget;
    ScreenStack&      mScreenStack;
    EventStage&       mNext;
};

#endif
