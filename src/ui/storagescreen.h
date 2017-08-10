#ifndef INCLUDED_STORAGESCREEN_H
#define INCLUDED_STORAGESCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelledwidget.h"
#include "ui/labelwidget.h"
#include "ui/widgetset.h"
#include "keyeventstage.h"

class Widget;

class StorageScreen : public KeyEventStage
{
public:
    StorageScreen();

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    Widget& rootWidget();
    
private:
    LabelWidget            mLabels[4];
    HStackWidget::Items<4> mItems;
    HStackWidget           mHStackWidget;
};

#endif










