#ifndef INCLUDED_KEYCONFIGSCREEN_H
#define INCLUDED_KEYCONFIGSCREEN_H

#include "ui/labelwidget.h"
#include "ui/labelledwidget.h"
#include "ui/hstackwidget.h"
#include "keyeventstage.h"

class Widget;

class KeyConfigScreen : public KeyEventStage
{
public:
    KeyConfigScreen();

public:
    virtual void processKeyEvent(const KeyEvent& event) override;

    Widget& rootWidget();
    
private:
    LabelledWidget<LabelWidget> mLayerLabel;
    LabelledWidget<LabelWidget> mRowLabel;
    LabelledWidget<LabelWidget> mColumnLabel;
    HStackWidget::Items<3>      mItems;
    HStackWidget                mHStackWidget;
    
private:
    KeyConfigScreen(const KeyConfigScreen&) = delete;
    KeyConfigScreen& operator=(const KeyConfigScreen&) = delete;
};

#endif
