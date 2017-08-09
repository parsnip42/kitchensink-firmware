#include "ui/benchmarkscreen.h"

#include "eventmanager.h"

#include <elapsedMillis.h>

namespace
{

class NullKeyStage : public KeyEventStage
{
public:
    virtual void processKeyEvent(const KeyEvent& event) override
    { }
};

}

BenchmarkScreen::BenchmarkScreen(EventManager& eventManager)
    : mEventManager(eventManager)
    , mStatusLabel()
    , mWidgetSet({ &mStatusLabel })
    , mListWidget(mWidgetSet.begin(), mWidgetSet.end(), LabelWidget::kPreferredHeight)
{ }

void BenchmarkScreen::processKeyEvent(const KeyEvent& event)
{
    
}

void BenchmarkScreen::run()
{
    auto start(millis());

    NullKeyStage nullNext;
    
    for (int i(0); i < 1000; ++i)
    {
        mEventManager.poll(nullNext);
    }
    
    auto end(millis());

    StrOStream os(mStatusLabel.text);
    
    os.appendInt(static_cast<int>(end-start));
    os.appendStr("ms (");
    os.appendInt(static_cast<int>(1000000 / (end-start)));
    os.appendStr(" polls/s)");

    mStatusLabel.invalidateWidget();
}

Widget& BenchmarkScreen::rootWidget()
{
    return mListWidget;
}
