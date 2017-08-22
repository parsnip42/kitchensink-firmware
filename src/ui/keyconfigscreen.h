#ifndef INCLUDED_KEYCONFIGSCREEN_H
#define INCLUDED_KEYCONFIGSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/labelwidget.h"
#include "ui/labelledwidget.h"
#include "ui/hstackwidget.h"
#include "ui/evententrywidget.h"
#include "ui/propertywidget.h"
#include "ui/screen.h"
#include "event/eventstage.h"

class KeySource;
class Widget;
class Timer;
class Layer;

class KeyConfigScreen : public Screen
{
public:
    KeyConfigScreen(Timer&     timer,
                    KeySource& keySource,
                    Layer&     layer);

public:
    virtual void processEvent(const Event& event) override;

public:
    virtual void screenInit() override;
    virtual Widget& rootWidget() override;
    
private:
    KeySource&                       mKeySource;
    Layer&                           mLayer;
    LabelledWidget<TextEntryWidget>  mTitleEntry;
    PropertyWidget                   mLocationProperty;
    LabelledWidget<EventEntryWidget> mEventEntry;
    HStackWidget::Items<3>           mItems;
    HStackWidget                     mHStackWidget;

private:
    KeyConfigScreen(const KeyConfigScreen&) = delete;
    KeyConfigScreen& operator=(const KeyConfigScreen&) = delete;
};

#endif
