#include "eventdispatcher.h"

#include "keymatrix.h"
#include "keymatrixevent.h"
#include "keystate.h"

EventDispatcher::EventDispatcher(const std::initializer_list<int>& rowMapping,
                                 const std::initializer_list<int>& columnMapping)
{
    mRowMapping.fill(0);

    size_t row(0);

    for (auto& index : rowMapping)
    {
        mRowMapping[row++] = index;
    }

    mColumnMapping.fill(0);

    size_t column(0);

    for (auto& index : columnMapping)
    {
        mColumnMapping[column++] = index;
    }
}
