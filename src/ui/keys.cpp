#include "ui/keys.h"

#include "keyid.h"

#include <keylayouts.h>

namespace UI
{
namespace Keys
{

bool up(const KeyId& keyId)
{
    return keyId == KeyId(KEY_UP);
}

bool down(const KeyId& keyId)
{
    return keyId == KeyId(KEY_DOWN);
}

bool ok(const KeyId& keyId)
{
    return (keyId == KeyId(KEY_ENTER)) || (keyId == KeyId(KEY_SPACE));
}
    
bool cancel(const KeyId& keyId)
{
    return keyId == KeyId(KEY_ESC);
}

}
}
