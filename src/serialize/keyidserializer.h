#ifndef INCLUDED_KEYIDSERIALIZER_H
#define INCLUDED_KEYIDSERIALIZER_H

#include "keyid.h"

#include "types/strbuf.h"
#include "types/strref.h"
#include "data/keycodes.h"
#include "types/strostream.h"

namespace KeyIdSerializer
{

void serialize(KeyId keyId, StrOStream& str);
void deserialize(const StrRef& keyIdStr, KeyId& keyId);

};

#endif /* INCLUDED_KEYIDSERIALIZER_H */
