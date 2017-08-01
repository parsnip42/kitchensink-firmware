#ifndef INCLUDED_COMBOWIDGET_H
#define INCLUDED_COMBOWIDGET_H

#include "keyeventstage.h"
#include "types/strbuf.h"
#include "ui/rectangle.h"
#include "ui/widget.h"
#include "ui/surface.h"

class EventManager;
class WidgetContainer;

class ComboWidget : public Widget
{
public:
    class DataSource
    {
    public:
        typedef StrBuf<20> ItemText;
        
    public:
        virtual void item(ItemText&   text,
                          std::size_t index) const = 0;
        
        virtual std::size_t size() const = 0;
    };

public:
    ComboWidget(Surface&                 surface,
                EventManager&            eventManager,
                WidgetContainer&         parent,
                ComboWidget::DataSource& dataSource);
    
    ComboWidget(ComboWidget&&) = default;
    
public:
    virtual void setFocused(bool focused) override;
    virtual void processKeyEvent(const KeyEvent& event) override;

    
    virtual Dimension getSize() const override
    {
        return mSize;
    }

    virtual void setSize(const Dimension& size) override
    {
        mSize = size;
    }

    void render(Surface::RowData& rowData, int row);

public:
    std::size_t selectedItem;
    bool        focused;
    
private:
    void paintSelection(uint8_t color);
    
private:
    Surface&                 mSurface;
    EventManager&            mEventManager;
    WidgetContainer&         mParent;
    ComboWidget::DataSource& mDataSource;
    Dimension                mSize;

private:
    ComboWidget(const ComboWidget&) = delete;
    ComboWidget& operator=(const ComboWidget&) = delete;
};


#endif
