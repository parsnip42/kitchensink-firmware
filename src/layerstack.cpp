#include "layerstack.h"
#include "layer.h"

#include <algorithm>

LayerStack::LayerStack()
{  }

KeyId LayerStack::at(int row, int column) const
{
    auto data(mLayerMask.data());

    int index(0);
    KeyId keyId;
    
    while (data)
    {
        if (data & 1)
        {
            KeyId next = mLayers[index].at(row, column);

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
    
void LayerStack::assignLayer(int index, const Layer& layer)
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
