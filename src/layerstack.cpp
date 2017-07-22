#include "layerstack.h"
#include "layer.h"

KeyId LayerStack::at(int row, int column) const
{
    KeyId keyId;
    
    auto layerIterator(mLayerMask.bitIterator());
    
    while (layerIterator.more())
    {
        auto index(layerIterator.next());
        auto next(mLayers[index].at(row, column));
        
        if (next != KeyId())
        {
            keyId = next;
        }
    }
    
    return keyId;
}

int LayerStack::activeLayer(int row, int column) const
{
    int activeIndex(0);

    auto layerIterator(mLayerMask.bitIterator());

    while (layerIterator.more())
    {
        auto index(layerIterator.next());
        auto next(mLayers[index].at(row, column));

        if (next != KeyId())
        {
            activeIndex = index;
        }
    }

    return activeIndex;
}

KeyId LayerStack::atIndex(int index, int row, int column) const
{
    return mLayers[index].at(row, column);
}

void LayerStack::setLayer(int index, bool enabled)
{
    mLayerMask[index] = enabled;
}

bool LayerStack::enabled(int index) const
{
    return mLayerMask[index];
}
