#ifndef INCLUDED_MENUSCREEN_H
#define INCLUDED_MENUSCREEN_H

#include "event/eventstage.h"
#include "event/event.h"
#include "types/objectsource.h"
#include "types/strbuf.h"
#include "types/strref.h"
#include "ui/menuwidget.h"
#include "ui/screen.h"

class ScreenStack;
class Widget;

class MenuScreen : public Screen
{
public:
    typedef MenuWidget::Item               Item;
    typedef ObjectSource<MenuWidget::Item> DataSource;
    
public:
    MenuScreen(const DataSource& dataSource,
               EventStage&       next);

public:
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;
    
private:
    MenuWidget   mMenuWidget;
    EventStage&  mNext;
};

#endif
