#ifndef INCLUDED_KEYPROCESSOR_H
#define INCLUDED_KEYPROCESSOR_H

#include "keyeventstage.h"
#include "layerstack.h"

#include <cstdint>

class KsKeyboard;
class KeyLocation;

class KeyProcessor
{
public:
    KeyProcessor(KsKeyboard& keyboard,
                 LayerStack& layerStack);

public:
    void pollKeyEvent(uint32_t       timeMs,
                      KeyEventStage& next);

    void pressAll(KeyEventStage& next);
    void releaseAll(KeyEventStage& next);

private:
    void processLayerChange(const LayerStack::Mask& currentMask,
                            const LayerStack::Mask& nextMask,
                            KeyEventStage&          next);

private:
    KsKeyboard&      mKeyboard;
    LayerStack&      mLayerStack;
    LayerStack::Mask mLayerMask;
    
private:
    KeyProcessor(const KeyProcessor&) = delete;
    KeyProcessor& operator=(const KeyProcessor&) = delete;
};

#endif
