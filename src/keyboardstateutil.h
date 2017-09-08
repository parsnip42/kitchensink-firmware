#ifndef INCLUDED_KEYBOARDSTATEUTIL_H
#define INCLUDED_KEYBOARDSTATEUTIL_H

class KeyboardState;
class MacroSet;
class LayerStack;

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState);
void store(const MacroSet& macroSet);
void store(const LayerStack& layerStack);

}

#endif
