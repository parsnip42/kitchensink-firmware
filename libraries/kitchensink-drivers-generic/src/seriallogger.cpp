#include "seriallogger.h"

#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "hardware/ctrlutil.h"

#ifdef KSINK_SERIALLOGGER
#include <usb_seremu.h>
#endif

SerialLogger::SerialLogger()
{
#ifdef KSINK_SERIALLOGGER
    Serial.begin(9600);
#endif
}

SerialLogger::~SerialLogger()
{
#ifdef KSINK_SERIALLOGGER
    Serial.end();
#endif
}

void SerialLogger::log(const StrRef& str)
{
#ifdef KSINK_SERIALLOGGER
    StrBuf<48> strBuf;
    StrOutStream oss(strBuf);

    oss.appendInt(CtrlUtil::nowMs(), "%8d");
    oss.appendStr(" : ");
    oss.appendStr(str);
    oss.appendChar('\n');
    
    Serial.write(strBuf.begin(), strBuf.length());
#endif
}
