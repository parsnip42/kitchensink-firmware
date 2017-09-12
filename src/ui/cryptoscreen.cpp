#include "ui/cryptoscreen.h"

#include "types/stroutstream.h"
#include "hardware/entropypool.h"

#include <mbedtls/aes.h>
#include <mbedtls/sha256.h>

CryptoScreen::CryptoScreen(EntropyPool& entropyPool)
    : mEntropyPool(entropyPool)
    , mPoolSize("Entropy Pool", 100)
    , mPoolContent()
    , mTestAES("mbedTLS AES", 100, "Testing")
    , mTestSHA256("mbedTLS SHA256", 100, "Testing")
    , mItems({{ mPoolSize,
                mPoolContent,
                mTestAES,
                mTestSHA256
                }})
    , mHStackWidget(mItems, true)
{
    {
        StrOutStream os(mPoolSize.value);
        
        os.appendInt(mEntropyPool.count());
        os.appendStr(" entries");
    }

    {
        StrOutStream os(mPoolContent.text);

        auto value(mEntropyPool.read());

        for (auto octet : value)
        {
            os.appendInt(octet, "%2.2x");
        }
    }
}

bool CryptoScreen::processEvent(const Event& event)
{
    return false;
}

void CryptoScreen::screenInit()
{
    {
        auto result(static_cast<int>(mbedtls_aes_self_test(0)));
        
        mTestAES.value = ((result == 0) ? "Pass" : "Fail");
        mTestAES.invalidateWidget();
    }
    
    {
        auto result(static_cast<int>(mbedtls_sha256_self_test(0)));
        
        mTestSHA256.value = ((result == 0) ? "Pass" : "Fail");
        mTestSHA256.invalidateWidget();
    }
}

Widget& CryptoScreen::rootWidget()
{
    return mHStackWidget;
}
