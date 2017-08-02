#ifndef INCLUDED_MENUSCREEN_H
#define INCLUDED_MENUSCREEN_H

#include "keyeventstage.h"
#include "keyid.h"
#include "types/objectsource.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/menulayout.h"
#include "ui/widgetcontainer.h"
#include "ui/hsplitwidget.h"
#include "ui/labelwidget.h"

class EventManager;
class Surface;

class MenuScreen : public KeyEventStage
                 , public WidgetContainer
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
    class MenuDataSource : public MenuLayout::DataSource
    {
    public:
        explicit MenuDataSource(const DataSource& dataSource);
        
    public:
        virtual void item(MenuItemWidget& widget, std::size_t index) const override;
        virtual std::size_t size() const override;

    private:
        const DataSource& mDataSource;
    };
    
public:
    MenuScreen(const StrRef&     title,
               const DataSource& dataSource,
               Surface&          surface,
               EventManager&     eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void invalidateParentRegion(const Rectangle& region) override;
    
    void poll();

private:
    void redraw();

private:
    StrRef         mTitle;
    Surface&       mSurface;
    EventManager&  mEventManager;
    MenuDataSource mMenuDataSource;
    MenuLayout     mMenuLayout;
    LabelWidget    mTitleWidget;
    HSplitWidget   mHSplit;
    bool           mQuit;
};

#endif
