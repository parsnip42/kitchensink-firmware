#ifndef INCLUDED_LAYERCONFIGSCREEN_H
#define INCLUDED_LAYERCONFIGSCREEN_H

#include "ui/textentrywidget.h"
#include "ui/labelledwidget.h"
#include "ui/hstackwidget.h"
#include "ui/evententrywidget.h"
#include "ui/keylocationwidget.h"
#include "ui/screen.h"
#include "ui/singlewidget.h"
#include "event/eventstage.h"

class KeySource;
class Widget;
class Timer;
class Layer;

class LayerConfigScreen : public Screen
{
public:
    LayerConfigScreen(Timer&     timer,
                      KeySource& keySource,
                      Layer&     layer);

public:
    virtual void processEvent(const Event& event) override;

public:
    virtual Widget& rootWidget() override;
    
private:
    KeySource&                        mKeySource;
    Layer&                            mLayer;
    LabelledWidget<TextEntryWidget>   mTitleEntry;
    LabelledWidget<KeyLocationWidget> mKeyLocation;
    LabelledWidget<EventEntryWidget>  mEventEntry;
    HStackWidget::Items<3>            mItems;
    HStackWidget                      mHStackWidget;
    SingleWidget                      mRootWidget;

private:
    LayerConfigScreen(const LayerConfigScreen&) = delete;
    LayerConfigScreen& operator=(const LayerConfigScreen&) = delete;
};

#endif
