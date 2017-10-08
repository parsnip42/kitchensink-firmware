#ifndef INCLUDED_DATAREFINSTREAM_H
#define INCLUDED_DATAREFINSTREAM_H

#include "types/instream.h"
#include "types/dataref.h"

class OutStream;

class DataRefInStream : public InStream
{
public:
    explicit DataRefInStream(const DataRef& data);

public:
    virtual std::size_t read(OutStream& os, std::size_t len) override;
    
private:
    DataRef     mData;
    std::size_t mPosition;
};


inline
DataRefInStream::DataRefInStream(const DataRef& data)
    : mData(data)
    , mPosition(0)
{ }

#endif
