#ifndef INCLUDED_SMARTKEYPROCESSOR_H
#define INCLUDED_SMARTKEYPROCESSOR_H

#include "keyeventstage.h"
#include "smartkeyset.h"

class SmartKeyProcessor : public KeyEventStage
{
public:
    SmartKeyProcessor(SmartKeySet&   smartKeys,
                      KeyEventStage& next);

public:
    virtual void processKeyEvent(const KeyEvent& event) override;
    
private:
    SmartKeySet&   mSmartKeys;
    KeyEventStage& mNext;
};

#endif
