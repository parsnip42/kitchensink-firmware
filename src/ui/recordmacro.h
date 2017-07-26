#ifndef INCLUDED_RECORDMACRO_H
#define INCLUDED_RECORDMACRO_H

#include "types/strref.h"
#include "keyevent.h"
#include "keyeventrecorder.h"

class Macro;
class KeyProcessor;
class Surface;

class RecordMacro
{    
public:
    RecordMacro(Surface&       surface,
                KeyProcessor&  keyProcessor,
                KeyEventStage& next);

public:
    bool create(const StrRef& title,
                Macro&        macro,
                bool          realtime);
    
private:
    Surface&       mSurface;
    KeyProcessor&  mKeyProcessor;
    KeyEventStage& mNext;
    
private:
    RecordMacro(const RecordMacro&) = delete;
    RecordMacro& operator=(const RecordMacro&) = delete;
};


inline
RecordMacro::RecordMacro(Surface&      surface,
                         KeyProcessor& keyProcessor,
                         KeyEventStage& next)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mNext(next)
{ }

#endif
