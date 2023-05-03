#include "hashtable.h"



void HashTableCtor (HashTable *htable, size_t (*hash_func)(const char *elem), size_t size)
{
    assert (htable    != nullptr);
    assert (hash_func != nullptr);

    htable -> hash_func = hash_func;
    htable -> size = size;
    htable -> data = (HashTableElem **) calloc (size, sizeof (htable -> data[0]));

    assert (htable -> data != nullptr);
}

void HashTableDtor (HashTable *htable)
{
    assert (htable != nullptr);

    for (size_t i = 0; i < htable -> size; i++) hashtable_list_dtor (htable -> data [i]);
    free (htable -> data);

    htable -> size = 0;
    htable -> hash_func = nullptr;
}

void hashtable_list_dtor (HashTableElem *elem)
{
    while (elem)
    {
        HashTableElem *next = elem -> next;

        free (elem);

        elem = next;
    }
}

void HashTableInsert (HashTable *htable, const char *value)
{
    assert (htable              != nullptr);
    assert (htable -> hash_func != nullptr);
    assert (htable -> data      != nullptr);
    assert (value               != nullptr);

    size_t hash = htable -> hash_func (value) % htable -> size;

    htable -> data [hash] = hashtable_list_insert (htable -> data [hash], value);
}

HashTableElem *hashtable_list_insert (HashTableElem *elem, const char *value)
{
    if (hashtable_list_find (elem, value) != nullptr) elem;

    HashTableElem *newelem = (HashTableElem *) calloc (1, sizeof (HashTableElem));
    assert (newelem != nullptr);

    newelem -> value = value;
    newelem -> next = elem;

    return newelem;
}

HashTableElem *hashtable_list_find (HashTableElem *elem, const char *value)
{
    while (elem && strcmp (elem -> value, value)) elem = elem -> next;
    return elem;
}
