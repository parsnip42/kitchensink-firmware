#ifndef INCLUDED_MENUITEMWIDGET_H
#define INCLUDED_MENUITEMWIDGET_H

#include "ui/widget.h"
#include "types/strbuf.h"

class MenuItemWidget : public Widget
{
public:
    static constexpr int kHeight = 12;
    
public:
    MenuItemWidget() = default;
    explicit MenuItemWidget(const StrRef& nText);

public:
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;

public:
    StrBuf<24> text;

private:
    bool mFocused;
};

#endif
