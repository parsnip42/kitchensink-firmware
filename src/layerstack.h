#ifndef INCLUDED_LAYERSTACK_H
#define INCLUDED_LAYERSTACK_H

#include "bitmask.h"
#include "keyid.h"
#include "layer.h"

#include <array>

class LayerStack
{
public:
    static const int MaxLayers = 10;
    
public:
    LayerStack();

public:
    KeyId at(int row, int column) const;
    int activeLayer(int row, int column) const;
    KeyId atIndex(int index, int row, int column) const;
    
public:
    void assignLayer(int index, const Layer& layer);
    void setLayer(int index, bool enabled);
    bool enabled(int index) const;
    
private:
    std::array<Layer, MaxLayers> mLayers;
    Bitmask<MaxLayers>           mLayerMask;
};

#endif
