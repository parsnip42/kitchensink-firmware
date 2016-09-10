#include "layerstack.h"
#include "layer.h"

#include <algorithm>

LayerStack::LayerStack()
{
    std::fill(mLayers.begin(), mLayers.end(), nullptr);
}


int LayerStack::at(int row, int column) const
{
    auto data(mLayerMask.data());

    int index(0);
    int value(0);
    
    while (data)
    {
        if ((data & 1) && mLayers[index])
        {
            value = mLayers[index]->at(row, column);
        }

        data >>= 1;
        ++index;
    }
    
    return value;
}
    
void LayerStack::assignLayer(const Layer* layer, int index)
{
    mLayers[index] = layer;
}

void LayerStack::enableLayer(int index)
{
    mLayerMask.set(index);
}

void LayerStack::disableLayer(int index)
{
    mLayerMask.clear(index);
}
