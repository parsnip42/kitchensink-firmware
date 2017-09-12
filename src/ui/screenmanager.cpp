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
#include "ui/storagescreen.h"
#include "ui/statusscreen.h"
#include "ui/layerconfigscreen.h"
#include "ui/multiconfigscreen.h"
#include "ui/smartconfigscreen.h"
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
               EventStage&    next)
        : mScreenManager(screenManager)
        , mNext(next)
    { }

public:
    virtual bool processEvent(const Event& event) override
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

private:
    ScreenManager& mScreenManager;
    EventStage&    mNext;
};

}

ScreenManager::ScreenManager(Surface&       surface,
                             EventManager&  eventManager,
                             KeyboardState& keyboardState,
                             EntropyPool&   entropyPool)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mKeyboardState(keyboardState)
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
            launch(mScreenEventQueue.pop(),
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
        launchEditMacro(mKeyboardState.macroSet,
                        screenEvent.index,
                        screenEvent);
        break;

    case ScreenEvent::Type::kRecordMacro:
        launchRecordMacro(mKeyboardState.macroSet,
                          screenEvent.index,
                          screenEvent);
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
    HomeScreen screen(mEventManager.timer,
                      mKeyboardState.smartKeySet,
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
    MenuScreen screen(mMenuDefinitions.getDataSource(menuId),
                      next);
    
    displayScreen(mMenuDefinitions.getTitle(menuId),
                  screen,
                  sourceEvent);
}

void ScreenManager::launchScreen(int                screenId,
                                 const ScreenEvent& sourceEvent)
{
    switch (screenId)
    {
    case 0:
    {
        StorageScreen screen;

        displayScreen("Storage",
                      screen,
                      sourceEvent);
        break;
    }
            
    case 1:
    {
        StatusScreen screen(mEventManager);

        displayScreen("Status",
                      screen,
                      sourceEvent);
        break;
    }
    
    case 2:
    {
        CryptoScreen screen(mEntropyPool);

        displayScreen("Cryptography",
                      screen,
                      sourceEvent);
        break;
    }

    default:
        break;
    }
}

void ScreenManager::launchEditMacro(MacroSet&          macroSet,
                                    int                macroId,
                                    const ScreenEvent& sourceEvent)
{
    EditMacroScreen screen(mEventManager.timer,
                           macroSet,
                           macroId,
                           mEventManager);

    displayScreen("Edit Macro",
                  screen,
                  sourceEvent);
}

void ScreenManager::launchRecordMacro(MacroSet&          macroSet,
                                      int                macroId,
                                      const ScreenEvent& sourceEvent)
{
    // FIXME: Cleanup special case.
    
    RecordMacroScreen screen(mEventManager.timer,
                             macroSet,
                             macroId,
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
            mScreenEventQueue.pop();
            break;
        }
    }

    KeyboardStateUtil::store(mKeyboardState.macroSet);
}

void ScreenManager::launchEditLayer(int                layerId,
                                    const ScreenEvent& sourceEvent)
{
    LayerConfigScreen screen(mEventManager.timer,
                             mEventManager.keySource,
                             mKeyboardState.layerStack[layerId]);
    
    displayScreen("Layer Configuration",
                  screen,
                  sourceEvent);

    KeyboardStateUtil::store(mKeyboardState.layerStack);
}

void ScreenManager::launchEditMultiKey(int                multiKeyId,
                                       const ScreenEvent& sourceEvent)
{
    MultiConfigScreen screen(mEventManager.timer,
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
    SmartConfigScreen screen(mEventManager.timer,
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
    AutoRepeat autoRepeat(mEventManager.timer,
                          screen);
    
    OutputSink output(*this, autoRepeat);
    
    TitleWidget titleWidget;
    
    titleWidget.text = title;
    
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
            auto event(mScreenEventQueue.peek());

            if (event.type == ScreenEvent::Type::kHome ||
                event == sourceEvent)
            {
                mScreenEventQueue.pop();
                break;
            }
            
            if (!transient(sourceEvent) && transient(event))
            {
                mScreenEventQueue.pop();
                mEventManager.flush(output);
                launch(event, output);
            }
            else
            {
                break;
            }
        }
    }
}

