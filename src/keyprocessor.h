#ifndef INCLUDED_KEYPROCESSOR_H
#define INCLUDED_KEYPROCESSOR_H

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
    KeyProcessor(KsKeyboard& keyboard,
                 LayerStack& layerStack);

public:
    virtual void pollKeyEvent(uint32_t       timeMs,
                              KeyEventStage& next) override;

    void untilKeyPress();
    
    void untilIdle();

    KeyLocation readKeyLocation();

    void pressAll(KeyEventStage& next);
    void releaseAll(KeyEventStage& next);

private:
    bool consumeEvent(const KeyEvent& event,
                      uint32_t        timeMs);
    
    void setLayer(int            index,
                  bool           enabled,
                  KeyEventStage& next);

    void pressLayer(int            index,
                    KeyEventStage& next);

    void releaseLayer(int            index,
                      KeyEventStage& next);
    
private:
    KsKeyboard&    mKeyboard;
    LayerStack&    mLayerStack;
    
private:
    KeyProcessor(const KeyProcessor&) = delete;
    KeyProcessor& operator=(const KeyProcessor&) = delete;
};

#endif
