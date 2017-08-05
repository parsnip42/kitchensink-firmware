#ifndef INCLUDED_TITLEWIDGET_H
#define INCLUDED_TITLEWIDGET_H

#include "ui/font.h"
#include "ui/widget.h"
#include "types/strbuf.h"
#include "types/strref.h"

class TitleWidget : public Widget
{
public:
    static constexpr int kPreferredHeight = Font::kHeight + 2;
    
public:
    explicit TitleWidget(const StrRef& nText = StrRef());

public:
    virtual void render(const RasterLine& rasterLine, int row) override;
    
public:
    StrBuf<48> text;
};

#endif
