#ifndef INCLUDED_BENCHMARKSCREEN_H
#define INCLUDED_BENCHMARKSCREEN_H

#include "ui/listwidget.h"
#include "ui/titlewidget.h"
#include "ui/labelwidget.h"
#include "ui/hsplitwidget.h"
#include "ui/widgetset.h"
#include "keyeventstage.h"

class EventManager;
class Widget;

class BenchmarkScreen : public KeyEventStage
{
public:
    explicit BenchmarkScreen(EventManager& eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    void run();
    Widget& rootWidget();

private:
    EventManager& mEventManager;
    TitleWidget   mTitleWidget;

    LabelWidget mStatusLabel;
    
    WidgetSet<1> mWidgetSet;
    ListWidget   mListWidget;
    HSplitWidget mHSplit;

};

#endif
