#ifndef INCLUDED_SERIALLOGGER_H
#define INCLUDED_SERIALLOGGER_H

#include "log/logger.h"

class SerialLogger : public Logger
{
public:
    SerialLogger();
    ~SerialLogger();

public:
    virtual void log(const StrRef& str);
};

#endif
