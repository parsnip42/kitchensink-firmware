#ifndef INCLUDED_COMBOWIDGET_H
#define INCLUDED_COMBOWIDGET_H

#include "types/strbuf.h"
#include "ui/rectangle.h"
#include "ui/widget.h"

class KeyProcessor;

class Surface;
class EventManager;

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
                ComboWidget::DataSource& dataSource);

public:
    virtual void redrawContent(bool focused) override;
    virtual void processKeyEvent(const KeyEvent& event) override;

public:
    std::size_t selectedItem;
    
    Rectangle region;
    
private:
    void paintSelection(uint8_t color);
    
private:
    Surface&                 mSurface;
    EventManager&            mEventManager;
    ComboWidget::DataSource& mDataSource;

private:
    ComboWidget(const ComboWidget&) = delete;
    ComboWidget& operator=(const ComboWidget&) = delete;
};


#endif
