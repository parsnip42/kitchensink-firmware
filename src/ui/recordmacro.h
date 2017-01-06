#ifndef INCLUDED_UI_RECORDMACRO_H
#define INCLUDED_UI_RECORDMACRO_H

#include "types/strref.h"
#include "keyevent.h"

#include <array>

class KeyProcessor;
class UsbKeyboard;

namespace UI { class Surface; }

namespace UI
{

class RecordMacro
{
public:
    typedef std::array<KeyEvent, 200> Macro;
    
public:
    constexpr RecordMacro(Surface&      surface,
                          KeyProcessor& keyProcessor,
                          UsbKeyboard&  usbKeyboard);

public:
    bool create(const Types::StrRef& title,
                bool                 realtime);
    
    const Macro& macro() const;
    
private:
    Surface&      mSurface;
    KeyProcessor& mKeyProcessor;
    UsbKeyboard&  mUsbKeyboard;
    Macro         mMacro;
    
private:
    RecordMacro(const RecordMacro&) = delete;
    RecordMacro& operator=(const RecordMacro&) = delete;
};


inline
constexpr RecordMacro::RecordMacro(Surface&      surface,
                                   KeyProcessor& keyProcessor,
                                   UsbKeyboard&  usbKeyboard)
    : mSurface(surface)
    , mKeyProcessor(keyProcessor)
    , mUsbKeyboard(usbKeyboard)
{ }

inline
const RecordMacro::Macro& RecordMacro::macro() const
{
    return mMacro;
}

}

#endif
