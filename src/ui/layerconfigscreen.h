#ifndef INCLUDED_LAYERCONFIGSCREEN_H
#define INCLUDED_LAYERCONFIGSCREEN_H

#include "event/eventstage.h"
#include "ui/buttonwidget.h"
#include "ui/evententrywidget.h"
#include "ui/hstackwidget.h"
#include "ui/keylocationwidget.h"
#include "ui/labelledwidget.h"
#include "ui/screen.h"
#include "ui/textentrywidget.h"

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
    virtual bool processEvent(const Event& event) override;
    virtual Widget& rootWidget() override;

private:
    void onLocationSelected();
    void onEventSelected();
    void onUpdate();
    
private:
    KeySource&                        mKeySource;
    Layer&                            mLayer;
    LabelledWidget<TextEntryWidget>   mTitleEntry;
    LabelledWidget<KeyLocationWidget> mKeyLocation;
    LabelledWidget<EventEntryWidget>  mEventEntry;
    ButtonWidget                      mUpdateButton;
    HStackWidget::Items<4>            mItems;
    HStackWidget                      mHStackWidget;

private:
    LayerConfigScreen(const LayerConfigScreen&) = delete;
    LayerConfigScreen& operator=(const LayerConfigScreen&) = delete;
};

#endif
