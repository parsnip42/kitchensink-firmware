#ifndef INCLUDED_UI_RECORDMACRO_H
#define INCLUDED_UI_RECORDMACRO_H

#include "types/strref.h"
#include "keyevent.h"

#include <array>

class KeyProcessor;

namespace UI { class Surface; }

namespace UI
{

class RecordMacro
{
public:
    typedef std::array<KeyEvent, 200> Macro;
    
public:
    constexpr RecordMacro(Surface&      surface,
                          KeyProcessor& keyProcessor);

public:
    bool create(const Types::StrRef& title,
                bool                 realtime);
    
    const Macro& macro() const;
    
private:
    Surface&      mSurface;
    KeyProcessor& mKeyProcessor;
    Macro         mMacro;
    
private:
    RecordMacro(const RecordMacro&) = delete;
    RecordMacro& operator=(const RecordMacro&) = Delete;
};


inline
constexpr RecordMacro::RecordMacro(Surface&      surface,
                                   KeyProcessor& keyProcessor)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
{ }

inline
const RecordMacro::Macro& RecordMacro::macro() const
{
    return mMacro;
}

}

#endif
