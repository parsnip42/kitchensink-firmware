#ifndef INCLUDED_MENUTITLEWIDGET_H
#define INCLUDED_MENUTITLEWIDGET_H

#include "ui/widget.h"
#include "ui/labelwidget.h"
#include "ui/textentrywidget.h"
#include "types/strbuf.h"

class EventManager;

class MenuTitleWidget : public Widget
                      , public WidgetContainer
{
public:
    MenuTitleWidget() = default;
    MenuTitleWidget(const StrRef& title,
                    EventManager& eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void regionInvalidated(const Rectangle& region) override;
    virtual void parented() override;
    
public:
    StrRef filter() const;
    
public:
    LabelWidget     mTitle;
    TextEntryWidget mSearch;
};

#endif
