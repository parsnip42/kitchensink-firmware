#ifndef INCLUDED_MACROSET_H
#define INCLUDED_MACROSET_H

#include "macro.h"
#include "macrodatapool.h"
#include "types/strref.h"
#include "types/strbuf.h"
#include "config.h"

#include <array>

template <std::size_t Size, std::size_t PoolSize>
class MacroSetImpl
{
private:
    typedef std::array<Macro, Size> MacroData;

public:
    MacroSetImpl();
    
public:
    std::size_t size() const;
    void reset();
    
private:
    MacroDataPool<Size, PoolSize> mMacroPool;
    MacroData                     mMacroData;
    
public:
    const Macro& operator[](std::size_t index) const;
    Macro& operator[](std::size_t index);

private:
    MacroSetImpl(const MacroSetImpl&) = delete;
    MacroSetImpl& operator=(const MacroSetImpl&) = delete;
};


class MacroSet : public MacroSetImpl<Config::kMacroCount, Config::kMacroPoolSize>
{
public:
    MacroSet() = default;
};


class SecureMacroSet : public MacroSetImpl<Config::kSMacroCount, Config::kSMacroPoolSize>
{
public:
    SecureMacroSet();

public:
    bool mLocked;
};


template <std::size_t Size, std::size_t PoolSize>
inline
std::size_t MacroSetImpl<Size, PoolSize>::size() const
{
    return mMacroData.size();
}

template <std::size_t Size, std::size_t PoolSize>
inline
const Macro& MacroSetImpl<Size, PoolSize>::operator[](std::size_t index) const
{
    return mMacroData[index];
}

template <std::size_t Size, std::size_t PoolSize>
inline
Macro& MacroSetImpl<Size, PoolSize>::operator[](std::size_t index)
{
    return mMacroData[index];
}

template <std::size_t Size, std::size_t PoolSize>
inline
MacroSetImpl<Size, PoolSize>::MacroSetImpl()
{
    for (std::size_t i = 0; i < mMacroData.size(); ++i)
    {
        mMacroData[i] = Macro(&mMacroPool.pool, i);
    }
}

template <std::size_t Size, std::size_t PoolSize>
inline
void MacroSetImpl<Size, PoolSize>::reset()
{
    mMacroPool.clear();

    for (std::size_t i = 0; i < mMacroData.size(); ++i)
    {
        mMacroData[i] = Macro(&mMacroPool.pool, i);
    }
}

inline
SecureMacroSet::SecureMacroSet()
    : mLocked(true)
{ }

#endif
