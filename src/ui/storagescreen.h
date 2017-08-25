#ifndef INCLUDED_STORAGESCREEN_H
#define INCLUDED_STORAGESCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/labelwidget.h"
#include "ui/widgetset.h"
#include "ui/screen.h"
#include "event/eventstage.h"

class Widget;

class StorageScreen : public Screen
{
public:
    StorageScreen();

public:
    virtual bool processEvent(const Event& event) override;
    
    virtual Widget& rootWidget() override;
    
private:
    LabelWidget            mLabels[4];
    HStackWidget::Items<4> mItems;
    HStackWidget           mHStackWidget;
};

#endif










