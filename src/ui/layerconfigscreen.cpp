#include "ui/layerconfigscreen.h"
#include "ui/keys.h"
#include "keysource.h"
#include "event/keyevent.h"
#include "serialize/eventserializer.h"

LayerConfigScreen::LayerConfigScreen(Timer&     timer,
                                     KeySource& keySource,
                                     Layer&     layer)
    : mKeySource(keySource)
    , mLayer(layer)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mKeyLocation("Location", 70, KeyLocationWidget(timer, keySource))
    , mEventEntry("Current", 70, EventEntryWidget(timer))
    , mItems({{ mTitleEntry, mKeyLocation, mEventEntry }})
    , mHStackWidget(mItems, true)
{
    mTitleEntry.widget.text = mLayer.name;
}

bool LayerConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& LayerConfigScreen::rootWidget()
{
    return mHStackWidget;
}










