#include "layerstack.h"
#include "layer.h"

KeyId LayerStack::at(const Mask& layerMask,
                     int         row,
                     int         column) const
{
    KeyId keyId;
    
    auto layerIterator(layerMask.bitIterator());
    
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

int LayerStack::activeLayer(const Mask& layerMask,
                            int         row,
                            int         column) const
{
    int activeIndex(0);

    auto layerIterator(layerMask.bitIterator());

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
