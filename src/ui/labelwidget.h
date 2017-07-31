#ifndef INCLUDED_LABELWIDGET_H
#define INCLUDED_LABELWIDGET_H

#include "ui/justify.h"
#include "ui/rectangle.h"
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
    void render(Surface::RowData& rowData, int row) const;

public:
    Rectangle  region;
    StrBuf<24> text;
    Justify    justify;
    bool       focused;
};

#endif
