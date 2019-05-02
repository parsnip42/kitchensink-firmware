#include "log/log.h"

Logger* Log::logger = nullptr;

void Log::setLogger(Logger* l)
{
    logger = l;
}

void Log::clearLogger()
{
    logger = nullptr;
}

void Log::log(const StrRef& str)
{
    if (logger)
    {
        logger->log(str);
    }
}
