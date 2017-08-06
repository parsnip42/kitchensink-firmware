#ifndef INCLUDED_MENUTITLEWIDGET_H
#define INCLUDED_MENUTITLEWIDGET_H

#include "ui/widget.h"
#include "ui/textentrywidget.h"
#include "types/strbuf.h"
#include "ui/titlewidget.h"

class Timer;

class MenuTitleWidget : public Widget
                      , public WidgetContainer
{
public:
    static constexpr int kPreferredHeight = std::max(TitleWidget::kPreferredHeight,
                                                     TextEntryWidget::kPreferredHeight);

public:
    MenuTitleWidget() = default;
    MenuTitleWidget(const StrRef& title,
                    Timer&        timer);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;
    virtual void regionInvalidated(const Rectangle& region) override;
    
public:
    StrRef filter() const;
    
public:
    TitleWidget     mTitle;
    TextEntryWidget mSearch;
};

#endif
