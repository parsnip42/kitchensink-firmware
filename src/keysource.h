#ifndef INCLUDED_KEYSOURCE_H
#define INCLUDED_KEYSOURCE_H

#include "keyeventstage.h"
#include "layerstack.h"

#include <cstdint>

class KsKeyboard;
class KeyLocation;

class KeySource
{
public:
    KeySource(KsKeyboard& keyboard,
              LayerStack& layerStack);

public:
    void setLayer(int layer, bool enabled);
    int topLayer();

    void pollKeyEvent(uint32_t       timeMs,
                      KeyEventStage& next);

    bool anyPressed();

private:
    void processLayerChange(const LayerStack::Mask& currentMask,
                            const LayerStack::Mask& nextMask,
                            KeyEventStage&          next);

private:
    KsKeyboard&      mKeyboard;
    LayerStack&      mLayerStack;
    LayerStack::Mask mLayerMask;
    
private:
    KeySource(const KeySource&) = delete;
    KeySource& operator=(const KeySource&) = delete;
};

#endif
