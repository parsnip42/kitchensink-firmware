#ifndef INCLUDED_WIDGET_H
#define INCLUDED_WIDGET_H

#include "keyeventstage.h"
#include "surface.h"

class Dimension;

class Widget : public KeyEventStage
{
public:
    Widget() = default;
    virtual ~Widget() = default;
    
public:
    virtual void processKeyEvent(const KeyEvent&) override;    
    virtual void setFocused(bool focused) = 0;
    virtual Dimension getSize() const = 0;
    virtual void setSize(const Dimension& nSize) = 0;
    virtual void render(Surface::RowData& rowData, int row) = 0;
};

#endif
