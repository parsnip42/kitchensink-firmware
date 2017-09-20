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
    , mHomeWidget(globalConfig.homeScreenColumns)
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
            if (homeLed.index < mSmartKeySet.size())
            {
                const auto& smartKey(mSmartKeySet[homeLed.index]);
                
                entry.text  = smartKey.name;
                entry.value = smartKey.enabled;
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

