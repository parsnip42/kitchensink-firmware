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
    static constexpr int kPreferredHeight = Font::kHeight;

public:
    explicit LabelWidget(const StrRef& nText,
                         Justify       nJustify = Justify::kLeft);

public:
    virtual void setFocused(bool focused) override;
    virtual void render(const RasterLine& rasterLine, int row) override;
    
public:
    StrBuf<48> text;
    Justify    justify;

private:
    bool mFocused;
};

#endif
