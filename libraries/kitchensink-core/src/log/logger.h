#ifndef INCLUDED_LOGGER_H
#define INCLUDED_LOGGER_H

#include "types/strref.h"

class Logger
{
public:
    virtual void log(const StrRef& str) = 0;
};

#endif
