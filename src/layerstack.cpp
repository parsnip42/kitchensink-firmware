#include "layerstack.h"
#include "layer.h"

#include <algorithm>

LayerStack::LayerStack()
{
    std::fill(mLayers.begin(), mLayers.end(), nullptr);
}


KeyId LayerStack::at(int row, int column) const
{
    auto data(mLayerMask.data());

    int index(0);
    KeyId keyId;
    
    while (data)
    {
        if ((data & 1) && mLayers[index])
        {
            KeyId next = mLayers[index]->at(row, column);

            if (next.type() != 0)
            {
                keyId = next;
            }
        }

        data >>= 1;
        ++index;
    }
    
    return keyId;
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
