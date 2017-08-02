#ifndef INCLUDED_COMBOWIDGET_H
#define INCLUDED_COMBOWIDGET_H

#include "keyeventstage.h"
#include "types/strbuf.h"
#include "ui/rectangle.h"
#include "ui/widget.h"
#include "ui/surface.h"

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
    explicit ComboWidget(ComboWidget::DataSource& dataSource);
    
    ComboWidget(ComboWidget&&) = default;
    
public:
    virtual void setFocused(bool focused) override;
    virtual void processKeyEvent(const KeyEvent& event) override;
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


