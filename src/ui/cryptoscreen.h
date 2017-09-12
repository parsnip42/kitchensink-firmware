#ifndef INCLUDED_CRYPTOSCREEN_H
#define INCLUDED_CRYPTOSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelwidget.h"
#include "ui/propertywidget.h"
#include "ui/screen.h"
#include "ui/widgetset.h"
#include "timer.h"

class EntropyPool;

class CryptoScreen : public Screen
{
public:
    CryptoScreen(Timer&       timer,
                 EntropyPool& entropyPool);

public:
    virtual bool processEvent(const Event& event) override;
    virtual void screenInit() override;
    virtual Widget& rootWidget() override;
        
private:
    Timer::Handle          mUpdateTimer;
    EntropyPool&           mEntropyPool;
    PropertyWidget         mTestAES;
    PropertyWidget         mTestSHA256;
    PropertyWidget         mPoolSize;
    LabelWidget            mPoolContent;
    HStackWidget::Items<4> mItems;
    HStackWidget           mHStackWidget;

};

#endif
