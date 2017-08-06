#ifndef INCLUDED_STORAGESCREEN_H
#define INCLUDED_STORAGESCREEN_H

#include "ui/textscreen.h"
#include "ui/listwidget.h"
#include "ui/titlewidget.h"
#include "ui/labelwidget.h"
#include "ui/hsplitwidget.h"
#include "ui/widgetset.h"
#include "keyeventstage.h"

class Surface;
class EventManager;

class StorageScreen : public KeyEventStage
{
public:
    StorageScreen(Surface&      surface,
                  EventManager& eventManager);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
    void poll();
    
private:
    Surface&                   mSurface;
    EventManager&              mEventManager;
    TitleWidget                mTitleWidget;

    LabelWidget                mStatusLabel;
    
    WidgetSet<1>               mWidgetSet;
    ListWidget                 mListWidget;
    HSplitWidget               mHSplit;
    bool                       mQuit;
};

#endif










