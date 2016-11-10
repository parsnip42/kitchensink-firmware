#include "macroset.h"

void MacroSet::setMacro(int index, const std::initializer_list<KeyEvent>& press)
{
    mMacroPool.insert(index, press.begin(), press.end());
}
