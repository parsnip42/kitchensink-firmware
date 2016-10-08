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
            auto next(mLayers[index].at(row, column));

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

int LayerStack::activeLayer(int row, int column) const
{
    auto data(mLayerMask.data());

    int index(0);
    int activeIndex(0);
    
    while (data)
    {
        if (data & 1)
        {
            auto next(mLayers[index].at(row, column));

            if (next.type() != 0)
            {
                activeIndex = index;
            }
        }

        data >>= 1;
        ++index;
    }
    
    return activeIndex;
}

KeyId LayerStack::atIndex(int index, int row, int column) const
{
    return mLayers[index].at(row, column);
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

bool LayerStack::enabled(int index) const
{
    return mLayerMask[index];
}
