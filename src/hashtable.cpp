#include "hashtable.h"

void HashTableCtor (HashTable *htable, uint64_t (*hash_func)(const char *elem), uint64_t size)
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

    uint64_t hash = htable -> hash_func (value) % htable -> size;

    htable -> data [hash] = hashtable_list_insert (htable -> data [hash], value);
}

HashTableElem *hashtable_list_insert (HashTableElem *elem, const char *value)
{
    if (hashtable_list_find (elem, value) != nullptr) elem;

    HashTableElem *newelem = (HashTableElem *) calloc (1, sizeof (HashTableElem));
    assert (newelem != nullptr);

    strncpy (newelem -> value, value, MAX_STRLEN);
    newelem -> next = elem;

    return newelem;
}

HashTableElem *hashtable_list_find (HashTableElem *elem, const char *value)
{
    while (elem && mystrcmp (elem -> value, value) != 0) elem = elem -> next;
    return elem;
}

const char *HashTableFind (HashTable *htable, const char *value)
{
    assert (htable              != nullptr);
    assert (htable -> hash_func != nullptr);
    assert (htable -> data      != nullptr);
    assert (value               != nullptr);

    uint64_t hash = htable -> hash_func (value) % htable -> size;

    HashTableElem *elem = hashtable_list_find_asm (htable -> data [hash], value);
    
    if (elem == nullptr) return nullptr;
    else                 return elem -> value;
}

void HashTableDelete (HashTable *htable, const char *value)
{
    assert (htable              != nullptr);
    assert (htable -> hash_func != nullptr);
    assert (htable -> data      != nullptr);
    assert (value               != nullptr);

    uint64_t hash = htable -> hash_func (value) % htable -> size;

    htable -> data [hash] = hashtable_list_delete (htable -> data [hash], value);
}

HashTableElem *hashtable_list_delete (HashTableElem *elem, const char *value)
{
    if (elem == nullptr) return nullptr;

    if (strncmp (elem -> value, value, MAX_STRLEN) == 0)
    {
        HashTableElem *ret = elem -> next;
        free (elem);
        return ret;
    }

    HashTableElem *ret =  elem;
    HashTableElem *prev = elem;
    elem = elem -> next;

    while (elem && strncmp (elem -> value, value, MAX_STRLEN) != 0)
    {
        prev = elem;
        elem = elem -> next;
    }
    
    if (elem)
    {
        prev -> next = elem -> next;
        free (elem);
    }
    return ret;
}

size_t GetListLen (HashTableElem *elem)
{
    size_t ret = 0;

    while (elem)
    {
        ret++;
        elem = elem -> next;
    }

    return ret;
}


inline HashTableElem *hashtable_list_find_asm (HashTableElem *elem, const char *value)
{
    __asm__
    (
            ".intel_syntax noprefix\n"

            "Next:\n"

            "test %1, %1\n"
            "jz Return\n"

            "mov rax, qword ptr [%1]\n"
            "xor rax, qword ptr [%2]\n"

            "jnz Not_eq\n"

            "mov rax, qword ptr [%1 + 8]\n"
            "xor rax, qword ptr [%2 + 8]\n"

            "jnz Not_eq\n"

            "mov rax, qword ptr [%1 + 16]\n"
            "xor rax, qword ptr [%2 + 16]\n"

            "jnz Not_eq\n"

            "mov rax, qword ptr [%1 + 24]\n"
            "xor rax, qword ptr [%2 + 24]\n"

            "jz Return\n"

            "Not_eq:\n"

            "mov rax, [%1 + 32]\n"
            "mov %1, rax\n"
            "jmp Next\n"

            "Return:\n"
            "mov %0, %1\n"

            ".att_syntax prefix\n"

        : "=r" (elem) : "r" (elem), "r" (value) : "%rax"
    );

    return elem;
}