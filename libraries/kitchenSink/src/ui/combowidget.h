#ifndef INCLUDED_COMBOWIDGET_H
#define INCLUDED_COMBOWIDGET_H

#include "event/eventstage.h"
#include "types/strbuf.h"
#include "types/objectsource.h"
#include "ui/rectangle.h"
#include "ui/widget.h"
#include "ui/surface.h"

class ComboWidget : public Widget
{
public:
    typedef StrBuf<24>         Item;
    typedef ObjectSource<Item> DataSource;

public:
    explicit ComboWidget(ComboWidget::DataSource& dataSource);
    
    ComboWidget(ComboWidget&&) = default;
    
public:
    virtual void setFocused(bool focused) override;
    virtual bool processEvent(const Event& event) override;
    virtual void render(const RasterLine& rasterLine, int row) override;

public:
    std::size_t selectedItem;
    bool        focused;
    
private:
    void paintSelection(uint8_t color);
    
private:
    ComboWidget::DataSource& mDataSource;

private:
    ComboWidget(const ComboWidget&) = delete;
    ComboWidget& operator=(const ComboWidget&) = delete;
};


#endif


