#ifndef INCLUDED_KVPAIR_H
#define INCLUDED_KVPAIR_H

#include <utility>

template <typename Key, typename Value>
class KVPair
{
public:
    KVPair() = default;
    
    KVPair(const Key&   nKey,
           const Value& nValue);

    KVPair(Key&&   nKey,
           Value&& nValue);

public:
    Key   key;
    Value value;
};

template <typename Key, typename Value>
inline
bool operator<(const KVPair<Key, Value>& a,
               const KVPair<Key, Value>& b)
{
    return a.key < b.key;
}

template <typename Key, typename Value>
inline
bool operator<(const KVPair<Key, Value>& a,
               const Key&               b)
{
    return a.key < b;
}

template <typename Key, typename Value>
inline
bool operator<(const Key&                a,
               const KVPair<Key, Value>& b)
{
    return a < b.key;
}

template <typename Key, typename Value>
inline
KVPair<Key, Value>::KVPair(const Key&   nKey,
                           const Value& nValue)
    : key(nKey)
    , value(nValue)
{ }

template <typename Key, typename Value>
inline
KVPair<Key, Value>::KVPair(Key&&   nKey,
                           Value&& nValue)
    : key(std::move(nKey))
    , value(std::move(nValue))
{ }


#endif /* INCLUDED_KVPAIR_H */
