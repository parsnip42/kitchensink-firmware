#include "ui/keyconfigscreen.h"
#include "ui/keys.h"
#include "keysource.h"
#include "event/keyevent.h"
#include "serialize/eventserializer.h"


#include "types/mappedobjectsource.h"



KeyConfigScreen::KeyConfigScreen(Timer&     timer,
                                 KeySource& keySource,
                                 Layer&     layer)
    : mKeySource(keySource)
    , mLayer(layer)
    , mTitleEntry("Name", 70, TextEntryWidget(timer))
    , mLocationProperty("Location", 70)
    , mEventEntry("Current", 70, EventEntryWidget(timer))
    , mItems({{ mTitleEntry, mLocationProperty, mEventEntry }})
    , mHStackWidget(mItems, true)
{
    mTitleEntry.widget.text = mLayer.name;
}

void KeyConfigScreen::processEvent(const Event& event)
{
    mHStackWidget.processEvent(event);
}

void KeyConfigScreen::screenInit()
{
    mHStackWidget.invalidateWidget();

    // auto location(mKeySource.readNextKeyLocation());
    
    // { 
    // }
    
    // {
    //     StrOStream os(mLocationProperty.value);
        
    //     os.reset();
    //     os.appendInt(location.row);
    //     os.appendStr(", ");
    //     os.appendInt(location.column);
    // }

    // auto event(mKeySource.layerStack[layer].at(location.row, location.column));
    
    // mEventEntry.widget.event = event;
    mEventEntry.widget.update();

    mHStackWidget.invalidateWidget();
}

Widget& KeyConfigScreen::rootWidget()
{
    return mHStackWidget;
}
