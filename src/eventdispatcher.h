#ifndef INCLUDED_EVENTDISPATCHER_H
#define INCLUDED_EVENTDISPATCHER_H

#include "keymatrix.h"

#include <array>
#include <functional>
#include <initializer_list>

class KeyMatrix;
class KeyMatrixEvent;

class EventDispatcher
{
public:
    typedef std::function<void(const KeyMatrixEvent&)> Callback;

public:
    EventDispatcher(const std::initializer_list<int>& rowMapping,
                    const std::initializer_list<int>& columnMapping);

public:
    void dispatch(const KeyMatrix::Mask& stateMask,
                  const KeyMatrix::Mask& deltaMask,
                  const Callback&        callback);

private:
    std::array<int, KeyMatrix::kRows>    mRowMapping;
    std::array<int, KeyMatrix::kColumns> mColumnMapping;

private:
    EventDispatcher(const EventDispatcher&);
    EventDispatcher& operator=(const EventDispatcher&);
};


#endif
