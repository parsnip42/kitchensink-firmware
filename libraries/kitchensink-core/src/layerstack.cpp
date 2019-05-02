#include "layerstack.h"
#include "layer.h"

Event LayerStack::at(const Mask& layerMask,
                     int         row,
                     int         column) const
{
    Event keyId;
    
    auto layerIterator(layerMask.bitIterator());
    
    while (layerIterator.more())
    {
        auto index(layerIterator.next());
        auto next(mLayers[index].at(row, column));
        
        if (next != Event())
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

        if (next != Event())
        {
            activeIndex = index;
        }
    }

    return activeIndex;
}

Event LayerStack::atIndex(int index, int row, int column) const
{
    return mLayers[index].at(row, column);
}

void LayerStack::clear()
{
    mLayers = Layers();
}
