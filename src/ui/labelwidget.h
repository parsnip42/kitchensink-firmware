#ifndef INCLUDED_LABELWIDGET_H
#define INCLUDED_LABELWIDGET_H

#include "ui/rectangle.h"
#include "ui/surface.h"

#include "types/strbuf.h"

#include <cstdint>

class StrRef;

class LabelWidget
{
public:
    enum Justify : uint8_t
    {
        kLeft   = 0,
        kRight  = 1,
        kCenter = 2
    };
    
public:
    LabelWidget(const Rectangle& nRegion,
                const StrRef&    nText,
                Justify          nJustify);

public:
    void render(Surface::RowData& rowData, int row) const;

public:
    Rectangle  region;
    StrBuf<24> text;
    Justify    justify;
};

#endif
