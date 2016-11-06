#ifndef INCLUDED_MACROELEMENT_H
#define INCLUDED_MACROELEMENT_H

#include "keyid.h"

#include <cstdint>

class MacroElement
{
public:
    enum class Action : uint8_t {
        kTap     = 0,
        kPress   = 1,
        kRelease = 2
    };
    
public:
    constexpr MacroElement(const KeyId& nKeyId  = KeyId(),
                           Action       nAction = Action::kTap);
                          
public:
    KeyId  keyId;
    Action action;
};


inline
constexpr MacroElement::MacroElement(const KeyId& nKeyId,
                                     Action       nAction)
    : keyId(nKeyId)
    , action(nAction)
{ }


#endif
