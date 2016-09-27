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

void LayerStack::setLayer(int index, bool enabled)
{
    if (enabled)
    {
        mLayerMask.set(index);
    }
    else
    {
        mLayerMask.clear(index);
    }
}

bool LayerStack::enabled(int layer) const
{
    return mLayerMask[layer];
}
