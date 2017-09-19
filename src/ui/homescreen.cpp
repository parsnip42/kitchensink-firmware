#include "ui/homescreen.h"

#include "event/event.h"
#include "event/ledmaskevent.h"
#include "event/invalidateevent.h"
#include "globalconfig.h"

HomeScreen::HomeScreen(const GlobalConfig& globalConfig,
                       const SmartKeySet&  smartKeySet,
                       Timer&              timer,
                       EventStage&         next)
    : mGlobalConfig(globalConfig)
    , mSmartKeySet(smartKeySet)
    , mDisplayTimeout(timer.createHandle())
    , mNext(next)
{
    for (std::size_t i(0);
         i < mHomeWidget.entries.size() && i < mGlobalConfig.homeLedSet.size();
         ++i)
    {
        const auto& homeLed(mGlobalConfig.homeLedSet[i]);
        auto& entry(mHomeWidget.entries[i]);

        entry.visible = true;

        switch (homeLed.type)
        {
        case HomeLed::Type::kKeyboard:
            switch (homeLed.index)
            {
            case HomeLed::kNumLock:
                entry.text = "Num Lock";
                break;
                
            case HomeLed::kCapsLock:
                entry.text = "Caps Lock";
                break;

            case HomeLed::kScrollLock:
                entry.text = "Scroll Lock";
                break;

            default:
                entry.visible = false;
            }
            break;

        case HomeLed::Type::kSmartKey:
            if (homeLed.index < smartKeySet.size())
            {
                entry.text = smartKeySet[homeLed.index].name;
            }
            else
            {
                entry.visible = false;
            }
            break;

        default:
            entry.visible = false;
            break;
        }
    }

    mHomeWidget.visible = false;
}

bool HomeScreen::processEvent(const Event& event)
{
    if (mDisplayTimeout.matches(event))
    {
        mHomeWidget.visible = false;
        mHomeWidget.invalidateWidget();
    }
    else if (event.is<LedMaskEvent>())
    {
        auto ledMaskEvent(event.get<LedMaskEvent>());
        
        mHomeWidget.entries[0].value = ledMaskEvent.numLock();
        mHomeWidget.entries[2].value = ledMaskEvent.capsLock();
        mHomeWidget.entries[4].value = ledMaskEvent.scrollLock();

        update();
    }
    else if (event.is<InvalidateEvent>())
    {
        mHomeWidget.entries[1].value = mSmartKeySet[0].enabled;
        mHomeWidget.entries[3].value = mSmartKeySet[2].enabled;
        update();
    }
    else
    {
         return mNext.processEvent(event);
    }

    return true;
}

Widget& HomeScreen::rootWidget()
{
    return mHomeWidget;
}

void HomeScreen::update()
{
    mHomeWidget.visible = true;
    mHomeWidget.invalidateWidget();
    mDisplayTimeout.schedule(mGlobalConfig.homeScreenTimeout);
}


