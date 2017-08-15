#include "ui/keyconfigscreen.h"
#include "ui/keys.h"
#include "keysource.h"
#include "event/keyevent.h"
#include "serialize/eventserializer.h"

KeyConfigScreen::KeyConfigScreen(KeySource& keySource)
    : mKeySource(keySource)
    , mLayerLabel("Layer", 70)
    , mLocationLabel("Location", 70)
    , mCurrentLabel("Current", 70)
    , mItems({{ mLayerLabel, mLocationLabel, mCurrentLabel }})
    , mHStackWidget(mItems, true)
{
    mHStackWidget.setFocused(false);
}

void KeyConfigScreen::processEvent(const Event& event)
{
    if (Keys::ok(event))
    {
        mLayerLabel.widget.text    = "Waiting";
        mLocationLabel.widget.text = "Waiting";
        mCurrentLabel.widget.text  = "Waiting";
        mHStackWidget.invalidateWidget();
                
        auto layer(mKeySource.topLayer());
        auto location(mKeySource.readNextKeyLocation());

        { 
            mLayerLabel.widget.text =
                mKeySource.layerStack[layer].name;
        }

        {
            StrOStream os(mLocationLabel.widget.text);
            os.reset();
            os.appendInt(location.row);
            os.appendStr(", ");
            os.appendInt(location.column);
        }
            
        {
            auto event(mKeySource.layerStack[layer].at(location.row, location.column));
            
            StrOStream os(mCurrentLabel.widget.text);
            os.reset();
            EventSerializer::serialize(event, os);
        }
            
        mHStackWidget.invalidateWidget();
    }
}

Widget& KeyConfigScreen::rootWidget()
{
    return mHStackWidget;
}
