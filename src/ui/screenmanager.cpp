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

            if (mScreenManager.mCurrent != screenEvent)
            {
                mScreenManager.mCurrent = screenEvent;
            }
            else
            {
                mScreenManager.mCurrent = ScreenEvent(ScreenEvent::Type::kHome, 0);
            }
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
    , mCurrent(ScreenEvent::Type::kHome, 0)
{ }

void ScreenManager::poll(EventStage& next)
{
    while (true)
    {
        launch(mCurrent);
    }
}

void ScreenManager::launch(const ScreenEvent& screenEvent)
{
    switch (screenEvent.type)
    {
    case ScreenEvent::Type::kMenu:
        launchMenu(screenEvent.index);
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
        launchEditLayer(mKeyboardState.layerStack,
                        screenEvent.index);
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
    auto current(mCurrent);
    
    HomeScreen screen(mEventManager.timer,
                      mKeyboardState.smartKeySet,
                      mEventManager.defaultOutput);
    
    OutputSink output(*this, screen);

    Surface::WidgetGuard guard(mSurface, screen.rootWidget());

    while (current == mCurrent)
    {
        mEventManager.poll(output);
    }

    mEventManager.flush(output);
}

void ScreenManager::launchMenu(int menuId)
{
    MenuScreen screen(mMenuDefinitions.getDataSource(menuId),
                      mEventManager);
    
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

    displayScreen("Edit Macro", screen);
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

void ScreenManager::launchEditLayer(LayerStack& layerStack,
                                    int         layerId)
{
    LayerConfigScreen screen(mEventManager.timer,
                             mEventManager.keySource,
                             mKeyboardState.layerStack[layerId]);
    
    displayScreen("Layer Configuration", screen);
}

void ScreenManager::launchEditMultiKey(int multiKeyId)
{
    MultiConfigScreen screen(mEventManager.timer,
                             mKeyboardState.multiSet[multiKeyId]);

    displayScreen("Multi Key Configuration", screen);   
}

void ScreenManager::launchEditSmartKey(int smartKeyId)
{
    SmartConfigScreen screen(mEventManager.timer,
                             mKeyboardState.smartKeySet[smartKeyId]);

    displayScreen("Smart Key Configuration", screen);
}

void ScreenManager::displayScreen(const StrRef& title,
                                  Screen&       screen)
{
    auto current(mCurrent);
    
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
    
    while (current == mCurrent)
    {
        mEventManager.poll(output);
    }

    mEventManager.flush(output);
}
