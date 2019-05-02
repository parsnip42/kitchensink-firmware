#include "seriallogger.h"

#include "types/strbuf.h"
#include "types/stroutstream.h"
#include "hardware/ctrlutil.h"

#include <usb_seremu.h>

SerialLogger::SerialLogger()
{
    Serial.begin(9600);
}

SerialLogger::~SerialLogger()
{
    Serial.end();
}

void SerialLogger::log(const StrRef& str)
{
    StrBuf<48> strBuf;
    StrOutStream oss(strBuf);

    oss.appendInt(CtrlUtil::nowMs(), "%8d");
    oss.appendStr(" : ");
    oss.appendStr(str);
    oss.appendChar('\n');
    
    Serial.write(strBuf.begin(), strBuf.length());
}
