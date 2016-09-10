#ifndef INCLUDED_KEYMATRIXEVENTDISPATCHER_H
#define INCLUDED_KEYMATRIXEVENTDISPATCHER_H

#include "keymatrix.h"

#include <array>
#include <functional>

class KeyMatrix;
class KeyMatrixEvent;

class KeyMatrixEventDispatcher
{
public:
    typedef std::function<void(const KeyMatrixEvent&)> Callback;

public:
    typedef std::array<int, KeyMatrix::Rows>    RowMapping;
    typedef std::array<int, KeyMatrix::Columns> ColumnMapping;

public:
    KeyMatrixEventDispatcher(const RowMapping&    rowMapping,
                             const ColumnMapping& columnMapping);
    
public:
    void dispatch(const KeyMatrix& keyMatrix,
                  const Callback&  callback);

private:
    const RowMapping    mRowMapping;
    const ColumnMapping mColumnMapping;
};


#endif
