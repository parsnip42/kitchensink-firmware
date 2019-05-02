#ifndef INCLUDED_LOG_H
#define INCLUDED_LOG_H

#include "log/logger.h"

class Log
{
private:
    static Logger* logger;

public:
    static void setLogger(Logger* l);
    static void clearLogger();
    static void log(const StrRef &str);
};

#define KS_LOG(x) Log::log(x);

#endif
