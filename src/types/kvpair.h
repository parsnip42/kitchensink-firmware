#ifndef INCLUDED_KVPAIR_H
#define INCLUDED_KVPAIR_H

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
    Key  key;
    Value value;
};


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
    : key(nKey)
    , value(nValue)
{ }


#endif /* INCLUDED_KVPAIR_H */
