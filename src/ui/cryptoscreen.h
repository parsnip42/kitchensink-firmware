#ifndef INCLUDED_CRYPTOSCREEN_H
#define INCLUDED_CRYPTOSCREEN_H

#include "ui/hstackwidget.h"
#include "ui/labelwidget.h"
#include "ui/propertywidget.h"
#include "ui/screen.h"
#include "ui/widgetset.h"

class EntropyPool;

class CryptoScreen : public Screen
{
public:
    explicit CryptoScreen(EntropyPool& entropyPool);

public:
    virtual bool processEvent(const Event& event) override;
    virtual void screenInit() override;
    virtual Widget& rootWidget() override;
        
private:
    EntropyPool&           mEntropyPool;
    PropertyWidget         mPoolSize;
    LabelWidget            mPoolContent;
    PropertyWidget         mTestAES;
    PropertyWidget         mTestSHA256;
    HStackWidget::Items<4> mItems;
    HStackWidget           mHStackWidget;

};

#endif
