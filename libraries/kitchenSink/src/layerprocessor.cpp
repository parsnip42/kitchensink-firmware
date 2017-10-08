#include "layerprocessor.h"

#include "event/event.h"
#include "keysource.h"
#include "event/layerevent.h"

LayerProcessor::LayerProcessor(EventStage& next)
    : keySource(nullptr)
    , mNext(next)
{ }

bool LayerProcessor::processEvent(const Event& event)
{
    if (event.is<LayerEvent>())
    {
        auto layerEvent(event.get<LayerEvent>());

        keySource->setLayer(layerEvent.layer,
                            layerEvent.enable);
    }
    else
    {
        mNext.processEvent(event);
    }

    return true;
}
