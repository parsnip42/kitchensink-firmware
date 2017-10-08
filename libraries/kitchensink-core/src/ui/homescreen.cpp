#include "ui/homescreen.h"

#include "event/event.h"
#include "event/ledmaskevent.h"
#include "event/invalidateevent.h"
#include "types/stroutstream.h"
#include "globalconfig.h"

HomeScreen::HomeScreen(const GlobalConfig& globalConfig,
                       const SmartKeySet&  smartKeySet,
                       TimerManager&              timer,
                       EventStage&         next)
    : mGlobalConfig(globalConfig)
    , mSmartKeySet(smartKeySet)
    , mDisplayTimeout(timer.createTimer())
    , mHomeWidget(globalConfig.homeScreenColumns)
    , mNext(next)
{
    for (std::size_t i(0);
         i < mHomeWidget.entries.size() && i < mGlobalConfig.homeLedSet.size();
         ++i)
    {
        const auto& homeLed(mGlobalConfig.homeLedSet[i]);
        auto& entry(mHomeWidget.entries[i]);

        entry.visible = (homeLed.type != HomeLed::Type::kNone);
        entry.text    = homeLed.text(mSmartKeySet);
        
        if (homeLed.type == HomeLed::Type::kSmartKey &&
            homeLed.index < mSmartKeySet.size())
        {
            entry.value = mSmartKeySet[homeLed.index].enabled;
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
        updateKeyboardKeys(event.get<LedMaskEvent>());
    }
    else if (event.is<InvalidateEvent>())
    {
        updateSmartKeys();
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

void HomeScreen::updateKeyboardKeys(const LedMaskEvent& event)
{
    bool dirty(false);

    for (std::size_t i(0);
         i < mHomeWidget.entries.size() && i < mGlobalConfig.homeLedSet.size();
         ++i)
    {
        const auto& homeLed(mGlobalConfig.homeLedSet[i]);
        auto& entry(mHomeWidget.entries[i]);

        if (entry.visible && homeLed.type == HomeLed::Type::kKeyboard)
        {
            bool state(entry.value);
            
            switch (homeLed.index)
            {
            case HomeLed::kNumLock:
                state = event.numLock();
                break;
                
            case HomeLed::kCapsLock:
                state = event.capsLock();
                break;

            case HomeLed::kScrollLock:
                state = event.scrollLock();
                break;
            }

            if (state != entry.value)
            {
                entry.value = state;
                dirty = true;
            }
        }
    }

    if (dirty)
    {
        show();
    }
}

void HomeScreen::updateSmartKeys()
{
    bool dirty(false);

    for (std::size_t i(0);
         i < mHomeWidget.entries.size() && i < mGlobalConfig.homeLedSet.size();
         ++i)
    {
        const auto& homeLed(mGlobalConfig.homeLedSet[i]);
        auto& entry(mHomeWidget.entries[i]);

        if (entry.visible && homeLed.type == HomeLed::Type::kSmartKey)
        {
            if (homeLed.index < mSmartKeySet.size())
            {
                const auto& smartKey(mSmartKeySet[homeLed.index]);

                if (entry.value != smartKey.enabled)
                {
                    entry.value = smartKey.enabled;
                    dirty = true;
                }
            }
        }
    }

    if (dirty)
    {
        show();
    }
}

void HomeScreen::show()
{
    mHomeWidget.visible = true;
    mHomeWidget.invalidateWidget();
    mDisplayTimeout.schedule(mGlobalConfig.homeScreenTimeout);
}

