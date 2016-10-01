#ifndef INCLUDED_DEBOUNCE_H
#define INCLUDED_DEBOUNCE_H

#include <keymatrix.h>

class Debounce
{
public:
    explicit Debounce(int latency);

public:
    bool scan(KeyMatrix& keyMatrix);

private:
    const int                         mLatency;
    std::array<int, KeyMatrix::kRows> mStableCount;
    KeyMatrix::Mask                   mState;
    KeyMatrix::Mask                   mDelta;
    
private:
    Debounce(const Debounce&);
    Debounce& operator=(const Debounce&);
};

#endif
