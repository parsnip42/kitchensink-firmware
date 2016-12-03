#include "ui/keys.h"

#include "keyid.h"

#include <keylayouts.h>

namespace UI
{
namespace Keys
{

bool up(const KeyId& keyId)
{
    return (keyId == KeyId(KEY_UP) ||
            keyId == KeyId(KEY_E) ||
            keyId == KeyId(KEY_I));
}

bool down(const KeyId& keyId)
{
    return (keyId == KeyId(KEY_DOWN) ||
            keyId == KeyId(KEY_D) ||
            keyId == KeyId(KEY_K));
}

bool ok(const KeyId& keyId)
{
    return ((keyId == KeyId(KEY_ENTER)) ||
            (keyId == KeyId(KEY_SPACE)));
}
    
bool cancel(const KeyId& keyId)
{
    return ((keyId == KeyId(KEY_ESC)) ||
            (keyId == KeyId::Action(KeyId::ActionType::kMenu, 0)));
}

}
}
