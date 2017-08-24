#include "screenmanager.h"

#include "autorepeat.h"
#include "keyboardstate.h"
#include "ui/menudefinitions.h"
#include "ui/hsplitwidget.h"
#include "ui/titlewidget.h"
#include "ui/menuscreen.h"
#include "ui/editmacroscreen.h"
#include "ui/recordmacroscreen.h"
#include "ui/storagescreen.h"
#include "ui/benchmarkscreen.h"
#include "ui/layerconfigscreen.h"
#include "ui/multiconfigscreen.h"
#include "ui/smartconfigscreen.h"
#include "ui/keys.h"
#include "ui/homescreen.h"
#include "types/strostream.h"
#include "event/screenevent.h"
#include "eventmanager.h"

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
    virtual void processEvent(const Event& event) override
    {
        if (event.is<ScreenEvent>())
        {
            auto screenEvent(event.get<ScreenEvent>());
            
            mScreenManager.mScreenEventQueue.pushBack(screenEvent);
        }
        else
        {
            mNext.processEvent(event);
        }
    }

private:
    ScreenManager& mScreenManager;
    EventStage&    mNext;
};

}

ScreenManager::ScreenManager(Surface&       surface,
                             EventManager&  eventManager,
                             KeyboardState& keyboardState)
    : mSurface(surface)
    , mEventManager(eventManager)
    , mKeyboardState(keyboardState)
    , mMenuDefinitions(keyboardState)
{
    mScreenEventQueue.pushBack(ScreenEvent(ScreenEvent::Type::kHome, 0));
}

void ScreenManager::poll(EventStage& next)
{
    while (true)
    {
        if (!mScreenEventQueue.empty())
        {
            launch(mScreenEventQueue.pop(),
                   mEventManager);
        }
    }
}

void ScreenManager::launch(const ScreenEvent& screenEvent,
                           EventStage&        next)
{
    switch (screenEvent.type)
    {
    case ScreenEvent::Type::kMenu:
        launchMenu(screenEvent.index,
                   next);
        break;

    case ScreenEvent::Type::kScreen:
        launchScreen(screenEvent.index);
        break;

    case ScreenEvent::Type::kEditMacro:
        launchEditMacro(mKeyboardState.macroSet,
                        screenEvent.index);
        break;

    case ScreenEvent::Type::kRecordMacro:
    case ScreenEvent::Type::kRecordMacroRT:
        launchRecordMacro(mKeyboardState.macroSet,
                          screenEvent.index,
                          screenEvent.type == ScreenEvent::Type::kRecordMacroRT);
        break;

    case ScreenEvent::Type::kEditLayer:
        launchEditLayer(screenEvent.index);
        break;

    case ScreenEvent::Type::kEditSmart:
        launchEditSmartKey(screenEvent.index);
        break;

    case ScreenEvent::Type::kEditMulti:
        launchEditMultiKey(screenEvent.index);
        break;

    default:
        launchHome();
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

    while (true)
    {
        mEventManager.poll(output);

        if (!mScreenEventQueue.empty())
        {
            auto event(mScreenEventQueue.pop());

            if (event.type != ScreenEvent::Type::kHome)
            {
                mEventManager.flush(output);
                launch(event, mEventManager.defaultOutput);
            }
            else
            {
                mEventManager.flush(output);
                launchMenu(0, mEventManager);
            }
        }
    }
}

void ScreenManager::launchMenu(int         menuId,
                               EventStage& next)
{
    MenuScreen screen(mMenuDefinitions.getDataSource(menuId),
                      next);
    
    displayScreen(mMenuDefinitions.getTitle(menuId),
                  screen);
}

void ScreenManager::launchScreen(int screenId)
{
    switch (screenId)
    {
    case 0:
    {
        StorageScreen screen;

        displayScreen("Storage", screen);
        break;
    }
            
    case 1:
    {
        BenchmarkScreen screen(mEventManager);

        displayScreen("Benchmarking", screen);
        break;
    }

    default:
        break;
    }
}

void ScreenManager::launchEditMacro(MacroSet& macroSet,
                                    int       macroId)
{
    EditMacroScreen screen(mEventManager.timer,
                           macroSet,
                           macroId,
                           mEventManager);

    displayScreen("Edit Macro", screen, false);
}

void ScreenManager::launchRecordMacro(MacroSet& macroSet,
                                      int       macroId,
                                      bool      realtime)
{
    RecordMacroScreen screen(mEventManager.timer,
                             macroSet,
                             macroId,
                             realtime,
                             mEventManager.defaultOutput);
    
    displayScreen("Record Macro", screen);
}

void ScreenManager::launchEditLayer(int layerId)
{
    LayerConfigScreen screen(mEventManager.timer,
                             mEventManager.keySource,
                             mKeyboardState.layerStack[layerId]);
    
    displayScreen("Layer Configuration", screen, false);
}

void ScreenManager::launchEditMultiKey(int multiKeyId)
{
    MultiConfigScreen screen(mEventManager.timer,
                             mKeyboardState.multiSet[multiKeyId]);

    displayScreen("Multi Key Configuration", screen, false);   
}

void ScreenManager::launchEditSmartKey(int smartKeyId)
{
    SmartConfigScreen screen(mEventManager.timer,
                             mKeyboardState.smartKeySet[smartKeyId]);

    displayScreen("Smart Key Configuration", screen, false);
}

void ScreenManager::displayScreen(const StrRef& title,
                                  Screen&       screen,
                                  bool          transient)
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

    if (transient)
    {
        ScreenEvent nextEvent(ScreenEvent::Type::kHome, 0);
        
        while (true)
        {
            mEventManager.poll(output);

            if (!mScreenEventQueue.empty())
            {
                nextEvent = mScreenEventQueue.pop();
                break;
            }
        }

        if (nextEvent.type != ScreenEvent::Type::kHome)
        {
            mEventManager.flush(output);
            launch(nextEvent, mEventManager);
        }
    }
    else
    {
        while (true)
        {
            mEventManager.poll(output);

            if (!mScreenEventQueue.empty())
            {
                auto event(mScreenEventQueue.pop());
                
                if (event.type != ScreenEvent::Type::kHome)
                {
                        
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
}





