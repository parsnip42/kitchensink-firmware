#include "layerprocessor.h"

#include "keyevent.h"
#include "keysource.h"

LayerProcessor::LayerProcessor(KeyEventStage& next)
    : keySource(nullptr)
    , mNext(next)
{ }

void LayerProcessor::processKeyEvent(const KeyEvent& event)
{
    auto keyId(event.keyId);

    if (keyId.type() == KeyId::Type::kLayer)
    {
        keySource->setLayer(keyId.value(), event.pressed);
    }
    else
    {
        mNext.processKeyEvent(event);
    }
}
