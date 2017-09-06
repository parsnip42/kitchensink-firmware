#ifndef INCLUDED_KEYBOARDSTATEUTIL_H
#define INCLUDED_KEYBOARDSTATEUTIL_H

class KeyboardState;
class MacroSet;

namespace KeyboardStateUtil
{

void load(KeyboardState& keyboardState);
void store(const MacroSet& macroSet);

}

#endif
