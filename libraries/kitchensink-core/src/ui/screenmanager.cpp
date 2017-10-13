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
                             KeyboardState& keyboardState,
                             KeyHardware&   keyHardware,
                             EntropyPool&   entropyPool)
    : mSurface(display)
    , mEventManager(eventManager)
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
        launchEditMacro(mKeyboardState.macroSet[screenEvent.index],
                        ScreenEvent::create(ScreenEvent::Type::kRecordMacro,
                                            screenEvent.index),
                        screenEvent);
        break;
        
    case ScreenEvent::Type::kRecordMacro:
        launchRecordMacro(mKeyboardState.macroSet[screenEvent.index],
                          screenEvent);
        
        KeyboardStateUtil::store(mKeyboardState.macroSet);
        break;

    case ScreenEvent::Type::kEditSMacro:
        launchEditMacro(mKeyboardState.secureMacroSet[screenEvent.index],
                        ScreenEvent::create(ScreenEvent::Type::kRecordSMacro,
                                            screenEvent.index),
                        screenEvent);
        break;

    case ScreenEvent::Type::kRecordSMacro:
        launchRecordMacro(mKeyboardState.secureMacroSet[screenEvent.index],
                          screenEvent);

        launchScreen(ScreenEvent::kMacroSave,
                     ScreenEvent(ScreenEvent::Type::kScreen,
                                 ScreenEvent::kMacroSave));
        break;
        
    case ScreenEvent::Type::kEditLayer:
        launchEditLayer(screenEvent.index,
                        screenEvent);
        break;

    case ScreenEvent::Type::kEditSmart:
        launchEditSmartKey(screenEvent.index,
                           screenEvent);
        break;

    case ScreenEvent::Type::kEditMulti:
        launchEditMultiKey(screenEvent.index,
                           screenEvent);
        break;

    default:
        break;
    }
}

void ScreenManager::launchHome()
{
    HomeScreen screen(mKeyboardState.globalConfig,
                      mKeyboardState.smartKeySet,
                      mEventManager.timerManager,
                      mEventManager.defaultOutput);
    
    OutputSink output(*this, screen);
    
    Surface::WidgetGuard guard(mSurface, screen.rootWidget());

    while (mScreenEventQueue.empty())
    {
        mEventManager.poll(output);
    }
}

void ScreenManager::launchMenu(int                menuId,
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

void ScreenManager::launchScreen(int                screenId,
                                 const ScreenEvent& sourceEvent)
{
    switch (screenId)
    {
    case ScreenEvent::kGlobalSettings:
    {
        GlobalConfigScreen screen(mKeyboardState.smartKeySet,
                                  mKeyboardState.globalConfig,
                                  mEventManager.timerManager,
                                  mEventManager);

        displayScreen("Global Settings",
                      screen,
                      sourceEvent);

        KeyboardStateUtil::store(mKeyboardState.globalConfig);
        break;
    }

    case ScreenEvent::kStatus:
    {
        StatusScreen screen(mKeyboardState,
                            mEventManager);

        displayScreen("Status",
                      screen,
                      sourceEvent);
        break;
    }
    
    case ScreenEvent::kCryptography:
    {
        CryptoScreen screen(mEventManager.timerManager,
                            mEntropyPool);

        displayScreen("Cryptography",
                      screen,
                      sourceEvent);
        break;
    }
    
    case ScreenEvent::kEventStream:
    {
        EventStreamScreen screen;

        displayScreen("Event Stream",
                      screen,
                      sourceEvent);
        break;
    }

    case ScreenEvent::kMacroUnlock:
    {
        UnlockScreen screen(mKeyboardState.secureMacroSet,
                            mEventManager.timerManager,
                            mEventManager);

        displayScreen("Unlock Secure Macros",
                      screen,
                      sourceEvent);
        break;
    }

    case ScreenEvent::kMacroSave:
    {
        SaveSecureScreen screen(mKeyboardState.secureMacroSet,
                                mEntropyPool,
                                mEventManager);

        displayScreen("Saving Secure Macros",
                      screen,
                      sourceEvent);

        break;
    }
    
    case ScreenEvent::kInitSecureMacros:
    {
        InitSecureMacroScreen screen(mKeyboardState.secureMacroSet,
                                     mEventManager.timerManager,
                                     mEventManager);
        
        displayScreen("Setup Secure Macros",
                      screen,
                      sourceEvent);

        break;
    }
    
    default:
        break;
    }
}

void ScreenManager::launchEditMacro(Macro&             macro,
                                    Event              recordEvent,
                                    const ScreenEvent& sourceEvent)
{
    EditMacroScreen screen(mEventManager.timerManager,
                           macro,
                           recordEvent,
                           mEventManager);

    displayScreen("Edit Macro",
                  screen,
                  sourceEvent);
}

void ScreenManager::launchRecordMacro(Macro&             macro,
                                      const ScreenEvent& sourceEvent)
{
    // FIXME: Cleanup special case.
    
    RecordMacroScreen screen(mEventManager.timerManager,
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

void ScreenManager::launchEditLayer(int                layerId,
                                    const ScreenEvent& sourceEvent)
{
    LayerConfigScreen screen(mEventManager.timerManager,
                             mKeyHardware,
                             mKeyboardState.layerStack[layerId]);
    
    displayScreen("Layer Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.layerStack);
}

void ScreenManager::launchEditMultiKey(int                multiKeyId,
                                       const ScreenEvent& sourceEvent)
{
    MultiConfigScreen screen(mEventManager.timerManager,
                             mKeyboardState.multiKeySet[multiKeyId],
                             mEventManager);

    displayScreen("Multi Key Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.multiKeySet);
}

void ScreenManager::launchEditSmartKey(int                smartKeyId,
                                       const ScreenEvent& sourceEvent)
{
    SmartConfigScreen screen(mEventManager.timerManager,
                             mKeyboardState.smartKeySet[smartKeyId],
                             mEventManager);

    displayScreen("Smart Key Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.smartKeySet);
}

void ScreenManager::displayScreen(const StrRef&      title,
                                  Screen&            screen,
                                  const ScreenEvent& sourceEvent)
{
    AutoRepeat autoRepeat(mEventManager.timerManager,
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

