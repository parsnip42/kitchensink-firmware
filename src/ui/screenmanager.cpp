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
#include "ui/keyconfigscreen.h"
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
            
            mScreenManager.pushScreen(screenEvent);
        }
        else if (Keys::cancel(event))
        {
            mScreenManager.popScreen();
        }
        
        mNext.processEvent(event);
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
{ }

void ScreenManager::pushScreen(const ScreenEvent& screenEvent)
{
    if (!mScreenStack.empty() &&
        (screenEvent.type == ScreenEvent::Type::kHome ||
         mScreenStack.top() == screenEvent))
    {
        mScreenStack.pop();
    }
    else if (!mScreenStack.full())
    {
        mScreenStack.push(screenEvent);
    }
}

void ScreenManager::popScreen()
{
    if (!mScreenStack.empty())
    {
        mScreenStack.pop();
    }
}

void ScreenManager::poll(EventStage& next)
{
    while (true)
    {
        flush();
        
        if (mScreenStack.empty())
        {
            HomeScreen homeScreen(mEventManager.timer,
                                  mKeyboardState.smartKeySet,
                                  mEventManager.defaultOutput);
            
            OutputSink output(*this, homeScreen);
            
            Surface::WidgetGuard guard(mSurface,
                                       homeScreen.rootWidget());

            while (!mScreenStack.dirty())
            {
                mEventManager.poll(output);
            }
        }
        else
        {
            launch(mScreenStack.top());
        }
    }
}

void ScreenManager::launch(const ScreenEvent& screenEvent)
{
    switch (screenEvent.type)
    {
    case ScreenEvent::Type::kHome:
        launchMenu(0);
        break;
        
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
        
    case ScreenEvent::Type::kEditSMacro:
        launchEditMacro(mKeyboardState.secureMacroSet,
                        screenEvent.index);
        break;

    case ScreenEvent::Type::kRecordSMacro:
    case ScreenEvent::Type::kRecordSMacroRT:
        launchRecordMacro(mKeyboardState.secureMacroSet,
                          screenEvent.index,
                          screenEvent.type == ScreenEvent::Type::kRecordSMacroRT);

        break;
    }
}

void ScreenManager::launchMenu(int menuId)
{
    MenuScreen screen(mMenuDefinitions.getDataSource(menuId),
                      mScreenStack,
                      mEventManager);
            
    AutoRepeat autoRepeat(mEventManager.timer,
                          screen);
    
    displayScreen(autoRepeat, screen.rootWidget());
}

void ScreenManager::launchScreen(int screenId)
{
    switch (screenId)
    {
    case 0:
    {
        StorageScreen screen;

        displayScreen(screen,
                      screen.rootWidget());
        break;
    }
            
    case 1:
    {
        BenchmarkScreen screen(mEventManager);

        displayScreen(screen,
                      screen.rootWidget());
        break;
    }

    case 2:
    {
        KeyConfigScreen screen(mEventManager.keySource);

        displayScreen(screen,
                      screen.rootWidget());
        break;
    }

    default:
        break;
    }
}

void ScreenManager::launchEditMacro(MacroSet& macroSet,
                                    int       macroId)
{
    EditMacroScreen screen(mScreenStack,
                           mEventManager.timer,
                           macroSet,
                           macroId);

    displayScreen(screen, screen.rootWidget());
}

void ScreenManager::launchRecordMacro(MacroSet& macroSet,
                                      int       macroId,
                                      bool      realtime)
{
    RecordMacroScreen screen(mScreenStack,
                             mEventManager.timer,
                             macroSet,
                             macroId,
                             realtime,
                             mEventManager.defaultOutput);
    
    displayScreen(screen, screen.rootWidget());
}

void ScreenManager::displayScreen(EventStage& stage,
                                  Widget&     content)
{
    OutputSink output(*this, stage);

    TitleWidget titleWidget;

    createTitlePath(titleWidget.text);

    HSplitWidget hSplit(titleWidget,       
                        content,
                        TitleWidget::kPreferredHeight);

    Surface::WidgetGuard guard(mSurface, hSplit);

    while (!mScreenStack.dirty())
    {
        mEventManager.poll(output);
    }
}

void ScreenManager::createTitlePath(const StrOStream& os)
{
    for (auto it(mScreenStack.begin()); it != mScreenStack.end(); ++it)
    {
        if (it != mScreenStack.begin())
        {
            os.appendStr(" : ");
        }
        
        createTitle(*it, os);
    }
}

void ScreenManager::createTitle(const ScreenEvent& screenEvent,
                                const StrOStream&  os)
{
    switch (screenEvent.type)
    {
    case ScreenEvent::Type::kHome:
    case ScreenEvent::Type::kMenu:
        os.appendStr(mMenuDefinitions.getTitle(screenEvent.index));
        break;

    case ScreenEvent::Type::kScreen:
        switch (screenEvent.index)
        {
        case 0:
            os.appendStr("Storage");
            break;
            
        case 1:
            os.appendStr("Benchmark");
            break;

        case 2:
            os.appendStr("Layout Configuration");
            break;
        }
        break;

    case ScreenEvent::Type::kEditMacro:
        os.appendStr("Edit Macro");
        break;

    case ScreenEvent::Type::kRecordMacro:
    case ScreenEvent::Type::kRecordMacroRT:
        os.appendStr("Record Macro");
        break;
        
    case ScreenEvent::Type::kEditSMacro:
        os.appendStr("Edit Secure Macro");
        break;

    case ScreenEvent::Type::kRecordSMacro:
    case ScreenEvent::Type::kRecordSMacroRT:
        os.appendStr("Record Secure Macro");
        break;

    default:
        break;
    }
}

void ScreenManager::flush()
{
    OutputSink output(*this, mEventManager.defaultOutput);
    
    mEventManager.flush(output);
}
