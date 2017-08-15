#ifndef INCLUDED_KEYCONFIGSCREEN_H
#define INCLUDED_KEYCONFIGSCREEN_H

#include "ui/labelwidget.h"
#include "ui/labelledwidget.h"
#include "ui/hstackwidget.h"
#include "event/eventstage.h"

class KeySource;
class Widget;

class KeyConfigScreen : public EventStage
{
public:
    explicit KeyConfigScreen(KeySource& keySource);

public:
    virtual void processEvent(const Event& event) override;

    Widget& rootWidget();
    
private:
    KeySource&                  mKeySource;
    LabelledWidget<LabelWidget> mLayerLabel;
    LabelledWidget<LabelWidget> mLocationLabel;
    LabelledWidget<LabelWidget> mCurrentLabel;
    HStackWidget::Items<3>      mItems;
    HStackWidget                mHStackWidget;
    
private:
    KeyConfigScreen(const KeyConfigScreen&) = delete;
    KeyConfigScreen& operator=(const KeyConfigScreen&) = delete;
};

#endif
