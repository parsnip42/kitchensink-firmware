#ifndef INCLUDED_PROPERTYWIDGET_H
#define INCLUDED_PROPERTYWIDGET_H

#include "ui/widget.h"
#include "types/strbuf.h"
#include "types/strref.h"

class PropertyWidget : public Widget
{
public:
    PropertyWidget(const StrRef& nKey,
                   int           nSeparation,
                   const StrRef& nValue = "");

public:
    virtual void render(const RasterLine& rasterLine, int row) override;
    virtual Dimension minimumSize() const override;

public:
    int separation;
    StrBuf<48> key;
    StrBuf<48> value;
};

#endif

