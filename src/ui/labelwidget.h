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
    LabelWidget(const StrRef&    nText,
                Justify          nJustify);

public:
    virtual void setFocused(bool nFocused) override;
    virtual Dimension getSize() const override;
    virtual void setSize(const Dimension& size) override;
    virtual void render(Surface::RowData& rowData, int row) override;
    
public:
    StrBuf<24> text;
    Justify    justify;
    bool       focused;

private:
    Dimension mSize;
};

#endif
