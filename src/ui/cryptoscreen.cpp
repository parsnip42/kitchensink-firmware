#include "ui/cryptoscreen.h"

#include "types/stroutstream.h"

#include <mbedtls/aes.h>
#include <mbedtls/sha256.h>

CryptoScreen::CryptoScreen(EntropyPool& entropyPool)
    : mEntropyPool(entropyPool)
    , mTestAES("mbedTLS AES", 100, "<Wait>")
    , mTestSHA256("mbedTLS SHA256", 100, "<Wait>")
    , mScanRate("Scan Rate", 100)
    , mItems({{ mTestAES,
                mTestSHA256,
                mScanRate }})
    , mHStackWidget(mItems, true)
{ }

bool CryptoScreen::processEvent(const Event& event)
{
    return false;
}

void CryptoScreen::screenInit()
{
    {
        StrOutStream os(mTestAES.value);

        os.reset();
        
        auto result(static_cast<int>(mbedtls_aes_self_test(0)));
        os.appendStr((result == 0) ? "Pass" : "Fail");
        
        mTestAES.invalidateWidget();
    }
    
    {
        StrOutStream os(mTestSHA256.value);

        os.reset();

        auto result(static_cast<int>(mbedtls_sha256_self_test(0)));
        os.appendStr((result == 0) ? "Pass" : "Fail");

        mTestSHA256.invalidateWidget();
    }
}

Widget& CryptoScreen::rootWidget()
{
    return mHStackWidget;
}
