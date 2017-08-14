#ifndef INCLUDED_KEYCONFIGSCREEN_H
#define INCLUDED_KEYCONFIGSCREEN_H

#include "ui/labelwidget.h"
#include "ui/labelledwidget.h"
#include "ui/hstackwidget.h"
#include "eventstage.h"

class Widget;

class KeyConfigScreen : public EventStage
{
public:
    KeyConfigScreen();

public:
    virtual void processEvent(const Event& event) override;

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
