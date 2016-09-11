#ifndef INCLUDED_LAYERSTACK_H
#define INCLUDED_LAYERSTACK_H

#include "bitmask.h"
#include "keyid.h"

#include <array>

class Layer;

class LayerStack
{
public:
    static const int MaxLayers = 10;
    
public:
    LayerStack();

public:
    KeyId at(int row, int column) const;
    
public:
    void assignLayer(const Layer* layer, int index);
    void enableLayer(int index);
    void disableLayer(int index);
    
private:
    std::array<const Layer*, MaxLayers> mLayers;
    Bitmask<MaxLayers>                  mLayerMask;
};

#endif
