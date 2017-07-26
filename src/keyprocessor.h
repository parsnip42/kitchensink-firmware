#ifndef INCLUDED_KEYPROCESSOR_H
#define INCLUDED_KEYPROCESSOR_H

#include "eventqueue.h"
#include "keyeventsource.h"
#include "keyeventstage.h"
#include "macroprocessor.h"
#include "multiprocessor.h"
#include "lockprocessor.h"
#include "timed.h"

class KsKeyboard;
class KeyLocation;
class LayerStack;

class KeyProcessor : public KeyEventSource
{
public:
    KeyProcessor(KsKeyboard&    keyboard,
                 LayerStack&    layerStack,
                 KeyEventStage& next);

public:
    virtual void pollKeyEvent(uint32_t timeMs) override;

    void untilKeyPress();
    
    void untilIdle();

    KeyLocation readKeyLocation();

private:
    bool consumeEvent(const KeyEvent& event,
                      uint32_t        timeMs);
    
    void setLayer(int index,
                  bool enabled);

    void pressLayer(int index);

    void releaseLayer(int index);

private:
    KsKeyboard&    mKeyboard;
    LayerStack&    mLayerStack;
    KeyEventStage& mNext;
    
private:
    KeyProcessor(const KeyProcessor&) = delete;
    KeyProcessor& operator=(const KeyProcessor&) = delete;
};

#endif
