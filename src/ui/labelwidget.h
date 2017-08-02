#ifndef INCLUDED_LABELWIDGET_H
#define INCLUDED_LABELWIDGET_H

#include "ui/dimension.h"
#include "ui/justify.h"
#include "ui/surface.h"
#include "ui/widget.h"
#include "ui/widgetcontainer.h"
#include "types/strbuf.h"

#include <cstdint>

class StrRef;

class LabelWidget : public Widget
{
public:
    LabelWidget(const StrRef& nText,
                Justify       nJustify);

public:
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    
public:
    StrBuf<24> text;
    Justify    justify;

private:
    bool mFocused;
};

#endif
