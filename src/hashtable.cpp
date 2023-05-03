#include "hashtable.h"



void HashTableCtor (HashTable *htable, size_t (*hash_func)(const char *elem), size_t size)
{
    assert (htable != nullptr);
    assert (hash_func != nullptr);

    htable -> size = size;
    htable -> hash = hash_func;
    htable -> data = (HashTableElem **) calloc (size, sizeof (htable -> data[0]));

    assert (htable -> data != nullptr);
}

void HashTableDtor (HashTable *htable)
{
    assert (htable != nullptr);

    for (size_t i = 0; i < htable -> size; i++) hashtable_list_dtor (htable -> data [i]);
    free (htable -> data);

    htable -> size = 0;
    htable -> hash = nullptr;
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