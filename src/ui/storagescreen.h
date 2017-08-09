#ifndef INCLUDED_STORAGESCREEN_H
#define INCLUDED_STORAGESCREEN_H

#include "ui/listwidget.h"
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
    LabelWidget  mStatusLabel;
    WidgetSet<1> mWidgetSet;
    ListWidget   mListWidget;
};

#endif










