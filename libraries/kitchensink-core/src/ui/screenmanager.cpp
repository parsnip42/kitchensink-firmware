#include "screenmanager.h"

#include "autorepeat.h"
#include "keyboardstate.h"
#include "ui/menudefinitions.h"
#include "ui/hsplitwidget.h"
#include "ui/titlewidget.h"
#include "ui/menuscreen.h"
#include "ui/cryptoscreen.h"
#include "ui/editmacroscreen.h"
#include "ui/recordmacroscreen.h"
#include "ui/eventstreamscreen.h"
#include "ui/statusscreen.h"
#include "ui/globalconfigscreen.h"
#include "ui/initsecuremacroscreen.h"
#include "ui/layerconfigscreen.h"
#include "ui/multiconfigscreen.h"
#include "ui/savesecurescreen.h"
#include "ui/smartconfigscreen.h"
#include "ui/unlockscreen.h"
#include "ui/keys.h"
#include "ui/homescreen.h"
#include "event/screenevent.h"
#include "eventmanager.h"
#include "keyboardstateutil.h"

namespace
{

class OutputSink : public EventStage
{
public:
    OutputSink(ScreenManager& screenManager,
               EventStage&    next);

public:
    virtual bool processEvent(const Event& event) override;

private:
    ScreenManager& mScreenManager;
    EventStage&    mNext;
};


OutputSink::OutputSink(ScreenManager& screenManager,
                       EventStage&    next)
    : mScreenManager(screenManager)
    , mNext(next)
{ }

bool OutputSink::processEvent(const Event& event)
{
    if (!mNext.processEvent(event))
    {
        if (event.is<ScreenEvent>())
        {
            auto screenEvent(event.get<ScreenEvent>());
            
            mScreenManager.mScreenEventQueue.pushBack(screenEvent);
        }
        else
        {
            return false;
        }
    }
        
    return true;
}

}

ScreenManager::ScreenManager(Display&       display,
                             EventManager&  eventManager,
                             TimerManager&  timerManager,
                             KeyboardState& keyboardState,
                             KeyHardware&   keyHardware,
                             EntropyPool&   entropyPool)
    : mSurface(display)
    , mEventManager(eventManager)
    , mTimerManager(timerManager)
    , mKeyboardState(keyboardState)
    , mKeyHardware(keyHardware)
    , mEntropyPool(entropyPool)
    , mMenuDefinitions(keyboardState)
{ }

void ScreenManager::poll()
{
    while (true)
    {
        mEventManager.flush(mEventManager.defaultOutput);

        if (!mScreenEventQueue.empty())
        {
            launch(mScreenEventQueue.popFront(),
                   mEventManager);
        }
        else
        {
            launchHome();
        }
    }
}

bool ScreenManager::transient(const ScreenEvent& screenEvent) const
{
    return (screenEvent.type == ScreenEvent::Type::kMenu);
}
                               
void ScreenManager::launch(const ScreenEvent& screenEvent,
                           EventStage&        next)
{
    switch (screenEvent.type)
    {
    case ScreenEvent::Type::kHome:
        launchMenu(0,
                   ScreenEvent(ScreenEvent::Type::kMenu, 0),
                   next);
        break;

    case ScreenEvent::Type::kMenu:
        launchMenu(screenEvent.index,
                   screenEvent,
                   next);
        break;

    case ScreenEvent::Type::kScreen:
        launchScreen(screenEvent.index,
                     screenEvent);
        break;

    case ScreenEvent::Type::kEditMacro:
        launchEditMacroScreen(mKeyboardState.macroSet[screenEvent.index],
                              ScreenEvent::create(ScreenEvent::Type::kRecordMacro,
                                                  screenEvent.index),
                              screenEvent);
        break;
        
    case ScreenEvent::Type::kRecordMacro:
        launchRecordMacroScreen(mKeyboardState.macroSet[screenEvent.index],
                                screenEvent);
        
        KeyboardStateUtil::store(mKeyboardState.macroSet);
        break;

    case ScreenEvent::Type::kEditSMacro:
        launchEditMacroScreen(mKeyboardState.secureMacroSet[screenEvent.index],
                              ScreenEvent::create(ScreenEvent::Type::kRecordSMacro,
                                                  screenEvent.index),
                              screenEvent);
        break;

    case ScreenEvent::Type::kRecordSMacro:
        launchRecordMacroScreen(mKeyboardState.secureMacroSet[screenEvent.index],
                                screenEvent);

        launchScreen(ScreenEvent::kMacroSave,
                     ScreenEvent(ScreenEvent::Type::kScreen,
                                 ScreenEvent::kMacroSave));
        break;
        
    case ScreenEvent::Type::kEditLayer:
        launchEditLayerScreen(screenEvent.index,
                              screenEvent);
        break;

    case ScreenEvent::Type::kEditSmart:
        launchEditSmartKeyScreen(screenEvent.index,
                                 screenEvent);
        break;

    case ScreenEvent::Type::kEditMulti:
        launchEditMultiKeyScreen(screenEvent.index,
                                 screenEvent);
        break;

    default:
        break;
    }
}

void ScreenManager::launchScreen(int                screenId,
                                 const ScreenEvent& sourceEvent)
{
    switch (screenId)
    {
    case ScreenEvent::kGlobalSettings:
        launchGlobalConfigScreen(sourceEvent);
        break;
        
    case ScreenEvent::kStatus:
        launchStatusScreen(sourceEvent);
        break;
        
    case ScreenEvent::kCryptography:
        launchCryptoScreen(sourceEvent);
        break;
        
    case ScreenEvent::kEventStream:
        launchEventStreamScreen(sourceEvent);
        break;

    case ScreenEvent::kMacroUnlock:
        launchMacroUnlockScreen(sourceEvent);
        break;

    case ScreenEvent::kMacroSave:
        launchMacroSaveScreen(sourceEvent);
        break;
    
    case ScreenEvent::kInitSecureMacros:
        launchInitSecureMacroScreen(sourceEvent);
        break;
    
    default:
        break;
    }
}

void ScreenManager::displayScreen(const StrRef&      title,
                                  Screen&            screen,
                                  const ScreenEvent& sourceEvent)
{
    AutoRepeat autoRepeat(mTimerManager,
                          mKeyboardState.globalConfig,
                          screen);
    
    OutputSink output(*this, autoRepeat);
    
    TitleWidget titleWidget;
    
    titleWidget.text = title;
    
    HSplitWidget hSplit(titleWidget,    
                        screen.rootWidget(),
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    bool completed(false);
    
    screen.screenCompleted = Action::trigger(completed);
    screen.screenInit();
    
    while (!completed)
    {
        mEventManager.poll(output);

        if (!mScreenEventQueue.empty())
        {
            auto event(mScreenEventQueue.peekFront());

            if (event.type == ScreenEvent::Type::kHome ||
                event == sourceEvent)
            {
                // Consume event and fall through.
                mScreenEventQueue.popFront();
                completed = true;
            }
            
            if (!transient(sourceEvent) && transient(event))
            {
                // Consume event and push new screen on top of this screen.
                mScreenEventQueue.popFront();
                mEventManager.flush(output);
                launch(event, output);
            }
            else
            {
                // Don't push onto this screen - fall through and let the next
                // appear.
                completed = true;
            }
        }
    }

    screen.screenExit();
    screen.screenCompleted = Action();
}

// Note the forced noinline below - without this, the optimiser will inline some
// of these functions and allocate stack memory for them individually in the
// caller statement. This wastes quite a lot of memory, especially when we're
// stacking screens together.
//
// While this isn't always the case, we want to explicitly force the current and
// future optimisers to only allocate stack memory for screens that we're using.


__attribute__ ((noinline)) void ScreenManager::launchHome()
{
    HomeScreen screen(mKeyboardState.globalConfig,
                      mKeyboardState.smartKeySet,
                      mTimerManager,
                      mEventManager.defaultOutput);
    
    OutputSink output(*this, screen);
    
    Surface::WidgetGuard guard(mSurface, screen.rootWidget());

    while (mScreenEventQueue.empty())
    {
        mEventManager.poll(output);
    }
}

__attribute__ ((noinline)) void ScreenManager::launchMenu(int                menuId,
                                                          const ScreenEvent& sourceEvent,
                                                          EventStage&        next)
{
    if ((menuId == MenuDefinitions::kSecureMacros ||
         menuId == MenuDefinitions::kEditSecureMacros) &&
        !mKeyboardState.secureMacroSet.unlocked())
    {
        auto unlockEvent(ScreenEvent(ScreenEvent::Type::kScreen,
                                     ScreenEvent::kMacroUnlock));

        launchScreen(ScreenEvent::kMacroUnlock, unlockEvent);
    }
    else
    {
        MenuScreen screen(mMenuDefinitions.getDataSource(menuId),
                          next);
        
        displayScreen(mMenuDefinitions.getTitle(menuId),
                      screen,
                      sourceEvent);
    }
}

__attribute__ ((noinline)) void ScreenManager::launchRecordMacroScreen(Macro&             macro,
                                                                       const ScreenEvent& sourceEvent)
{
    // FIXME: Cleanup special case.
    
    RecordMacroScreen screen(mTimerManager,
                             macro,
                             mEventManager.defaultOutput);
    
    OutputSink output(*this, screen);
    
    TitleWidget titleWidget;
    
    titleWidget.text = "Record Macro";
    
    HSplitWidget hSplit(titleWidget,    
                        screen.rootWidget(),
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    screen.screenInit();

    while (true)
    {
        mEventManager.poll(output);

        if (!mScreenEventQueue.empty())
        {
            mScreenEventQueue.popFront();
            break;
        }
    }

    screen.screenExit();
}

__attribute__ ((noinline)) void ScreenManager::launchEditLayerScreen(int                layerId,
                                                                     const ScreenEvent& sourceEvent)
{
    LayerConfigScreen screen(mTimerManager,
                             mKeyHardware,
                             mKeyboardState.layerStack[layerId]);
    
    displayScreen("Layer Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.layerStack);
}

__attribute__ ((noinline)) void ScreenManager::launchEditMultiKeyScreen(int                multiKeyId,
                                                                        const ScreenEvent& sourceEvent)
{
    MultiConfigScreen screen(mTimerManager,
                             mKeyboardState.multiKeySet[multiKeyId],
                             mEventManager);

    displayScreen("Multi Key Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.multiKeySet);
}

__attribute__ ((noinline)) void ScreenManager::launchEditSmartKeyScreen(int                smartKeyId,
                                                                        const ScreenEvent& sourceEvent)
{
    SmartConfigScreen screen(mTimerManager,
                             mKeyboardState.smartKeySet[smartKeyId],
                             mEventManager);

    displayScreen("Smart Key Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.smartKeySet);
}


__attribute__ ((noinline)) void ScreenManager::launchEditMacroScreen(Macro&             macro,
                                                                     Event              recordEvent,
                                                                     const ScreenEvent& sourceEvent)
{
    EditMacroScreen screen(mTimerManager,
                           macro,
                           recordEvent,
                           mEventManager);

    displayScreen("Edit Macro",
                  screen,
                  sourceEvent);
}


__attribute__ ((noinline)) void ScreenManager::launchGlobalConfigScreen(const ScreenEvent& sourceEvent)
{
    GlobalConfigScreen screen(mKeyboardState.smartKeySet,
                              mKeyboardState.globalConfig,
                              mTimerManager,
                              mEventManager);

    displayScreen("Global Settings",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.globalConfig);
}

__attribute__ ((noinline)) void ScreenManager::launchStatusScreen(const ScreenEvent& sourceEvent)
{
    StatusScreen screen(mKeyboardState,
                        mEventManager,
                        mTimerManager);
    
    displayScreen("Status",
                  screen,
                  sourceEvent);
}

__attribute__ ((noinline)) void ScreenManager::launchCryptoScreen(const ScreenEvent& sourceEvent)
{
    CryptoScreen screen(mTimerManager,
                        mEntropyPool);
    
    displayScreen("Cryptography",
                  screen,
                  sourceEvent);
}

__attribute__ ((noinline)) void ScreenManager::launchEventStreamScreen(const ScreenEvent& sourceEvent)
{
    EventStreamScreen screen;

    displayScreen("Event Stream",
                  screen,
                  sourceEvent);
}

__attribute__ ((noinline)) void ScreenManager::launchMacroUnlockScreen(const ScreenEvent& sourceEvent)
{
    UnlockScreen screen(mKeyboardState.secureMacroSet,
                        mTimerManager,
                        mEventManager);
    
    displayScreen("Unlock Secure Macros",
                  screen,
                  sourceEvent);
}

__attribute__ ((noinline)) void ScreenManager::launchMacroSaveScreen(const ScreenEvent& sourceEvent)
{
    SaveSecureScreen screen(mKeyboardState.secureMacroSet,
                            mEntropyPool,
                            mEventManager);
    
    displayScreen("Saving Secure Macros",
                  screen,
                  sourceEvent);
}

__attribute__ ((noinline)) void ScreenManager::launchInitSecureMacroScreen(const ScreenEvent& sourceEvent)
{
    InitSecureMacroScreen screen(mKeyboardState.secureMacroSet,
                                 mTimerManager,
                                 mEventManager);
    
    displayScreen("Setup Secure Macros",
                  screen,
                  sourceEvent);
}
