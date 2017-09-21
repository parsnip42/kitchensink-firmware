#include "ui/cryptoscreen.h"

#include "types/stroutstream.h"
#include "hardware/entropypool.h"

#include <mbedtls/aes.h>
#include <mbedtls/sha256.h>

CryptoScreen::CryptoScreen(Timer&       timer,
                           EntropyPool& entropyPool)
    : mUpdateTimer(timer.createHandle())
    , mEntropyPool(entropyPool)
    , mTestAES("mbedTLS AES", 100, "Testing")
    , mTestSHA256("mbedTLS SHA256", 100, "Testing")
    , mPoolSize("Entropy Pool", 100)
    , mPoolContent()
    , mItems({{ mTestAES,
                mTestSHA256,
                mPoolSize,
                mPoolContent
                }})
    , mHStackWidget(mItems, true)
{
    mUpdateTimer.scheduleRepeating(0, 3000);
}

bool CryptoScreen::processEvent(const Event& event)
{
    if (mUpdateTimer.matches(event))
    {
        {
            StrOutStream os(mPoolSize.value);

            os.reset();
            os.appendInt(mEntropyPool.count());
            os.appendStr(" entries");

            mPoolSize.invalidateWidget();
        }

        {
            StrOutStream os(mPoolContent.text);

            auto value(mEntropyPool.read());

            os.reset();
        
            for (auto octet : value)
            {
                os.appendInt(octet, "%2.2x");
            }

            mPoolContent.invalidateWidget();
        }

        return true;
    }

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