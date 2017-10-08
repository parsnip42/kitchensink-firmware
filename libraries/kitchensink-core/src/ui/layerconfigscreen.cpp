#include "ui/layerconfigscreen.h"
#include "ui/keys.h"
#include "keysource.h"
#include "event/keyevent.h"
#include "serialize/eventserializer.h"

LayerConfigScreen::LayerConfigScreen(TimerManager&     timer,
                                     KeySource& keySource,
                                     Layer&     layer)
    : mKeySource(keySource)
    , mLayer(layer)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mKeyLocation("Location", 70, KeyLocationWidget(timer, keySource))
    , mEventEntry("Current", 70, EventEntryWidget(timer))
    , mUpdateButton("Update")
    , mItems({{ mTitleEntry,
                mKeyLocation,
                mEventEntry,
                mUpdateButton }})
    , mHStackWidget(mItems, true)
{
    mTitleEntry.widget.text = mLayer.name;

    mKeyLocation.widget.locationSelected = Action::memFn<LayerConfigScreen,
                                                         &LayerConfigScreen::onLocationSelected>(this);

    mEventEntry.widget.eventSelected = Action::memFn<LayerConfigScreen,
                                                     &LayerConfigScreen::onEventSelected>(this);
    
    mUpdateButton.activated = Action::memFn<LayerConfigScreen,
                                            &LayerConfigScreen::onUpdate>(this);
}

bool LayerConfigScreen::processEvent(const Event& event)
{
    return mHStackWidget.processEvent(event);
}

Widget& LayerConfigScreen::rootWidget()
{
    return mHStackWidget;
}

void LayerConfigScreen::onLocationSelected()
{
    const auto& location(mKeyLocation.widget.location);

    mEventEntry.widget.event = mLayer.at(location.row, location.column);
    
    mHStackWidget.setFocused(mEventEntry);
    mHStackWidget.invalidateWidget();
}

void LayerConfigScreen::onEventSelected()
{
    mHStackWidget.setFocused(mUpdateButton);
    mHStackWidget.invalidateWidget();
}

void LayerConfigScreen::onUpdate()
{
    mLayer.name = mTitleEntry.widget.text;

    const auto& location(mKeyLocation.widget.location);
    
    mLayer.set(location.row,
               location.column,
               mEventEntry.widget.event);

    mKeyLocation.widget.clear();
    mEventEntry.widget.event = Event();
    mHStackWidget.setFocused(mKeyLocation);
    mHStackWidget.invalidateWidget();
}





