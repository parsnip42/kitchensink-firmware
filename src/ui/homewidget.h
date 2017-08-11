#ifndef INCLUDED_HOMEWIDGET_H
#define INCLUDED_HOMEWIDGET_H

#include "ui/widget.h"

class HomeWidget : public Widget
{
public:
    class Entry
    {
    public:
        Entry();
        
    public:
        StrRef text;
        bool   value;
        bool   visible;
    };
    
public:
    HomeWidget();

public:
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual void parented() override;

private:
    void renderIndicator(const Entry&      entry,
                         const RasterLine& rasterLine,
                         int               row);
    
public:
    std::array<Entry, 9> entries;
    bool                 visible;

private:
    int mWidgetWidth;
    int mWidgetHeight;
    int mWidgetColumns;
};

#endif
