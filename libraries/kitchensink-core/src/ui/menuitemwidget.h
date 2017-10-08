#ifndef INCLUDED_MENUITEMWIDGET_H
#define INCLUDED_MENUITEMWIDGET_H

#include "ui/font.h"
#include "ui/widget.h"
#include "types/strbuf.h"

class MenuItemWidget : public Widget
{
public:
    static constexpr int kPreferredHeight = Font::kHeight;
    
public:
    MenuItemWidget() = default;
    MenuItemWidget(const StrRef& nText,
                   const StrRef& nShortcut);

public:
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;

public:
    StrBuf<24> text;
    StrBuf<24> shortcut;
    StrBuf<24> filter;
    
private:
    bool mFocused;
};

#endif
