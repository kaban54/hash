#include "hashtable.h"

void HashTableCtor (HashTable *htable, uint64_t (*hash_func)(const char *elem), uint64_t size)
{
    assert (htable    != nullptr);
    assert (hash_func != nullptr);

    htable -> hash_func = hash_func;
    htable -> size = size;
    htable -> data = (HashTableList *) calloc (size, sizeof (htable -> data[0]));

    for (size_t index = 0; index < htable -> size; index++) hashtable_list_ctor (htable -> data + index, LIST_BASE_CAP);

    assert (htable -> data != nullptr);
}

void hashtable_list_ctor (HashTableList *lst, size_t capacity)
{
    lst -> data = (const char **) calloc (capacity, sizeof (lst -> data [0]));
    assert (lst -> data != nullptr);

    lst -> capacity = capacity;
    lst -> size     = 0;
}

void HashTableDtor (HashTable *htable)
{
    assert (htable != nullptr);

    for (size_t index = 0; index < htable -> size; index++) hashtable_list_dtor (htable -> data + index);
    free (htable -> data);

    htable -> size = 0;
    htable -> hash_func = nullptr;
}

void hashtable_list_dtor (HashTableList *lst)
{
    free (lst -> data);
    lst -> size     = 0;
    lst -> capacity = 0;
}

void HashTableInsert (HashTable *htable, const char *value)
{
    assert (htable              != nullptr);
    assert (htable -> hash_func != nullptr);
    assert (htable -> data      != nullptr);
    assert (value               != nullptr);

    uint64_t hash = htable -> hash_func (value) % htable -> size;

    hashtable_list_insert (htable -> data + hash, value);
}

void hashtable_list_insert (HashTableList *lst, const char *value)
{
    if (hashtable_list_find (lst, value) != nullptr) return;

    if (lst -> size >= lst -> capacity) hashtable_list_resize (lst, lst -> capacity == 0 ? LIST_BASE_CAP : lst -> capacity * 2);

    lst -> data [lst -> size] = value;
    lst -> size ++;
}

void hashtable_list_resize (HashTableList *lst, size_t new_cap)
{
    assert (new_cap >= lst -> size);

    lst -> data = (const char **) realloc (lst -> data, new_cap * sizeof (lst -> data [0]));

    assert (lst -> data != nullptr);
    
    lst -> capacity = new_cap;
}

const char *HashTableFind (HashTable *htable, const char *value)
{
    assert (htable              != nullptr);
    assert (htable -> hash_func != nullptr);
    assert (htable -> data      != nullptr);
    assert (value               != nullptr);

    uint64_t hash = htable -> hash_func (value) % htable -> size;

    return hashtable_list_find (htable -> data + hash, value);
}

const char *hashtable_list_find (HashTableList *lst, const char *value)
{
    for (size_t index = 0; index < lst -> size; index++)
    {
        if (strcmp (value, lst -> data [index]) == 0) return lst -> data [index];
    }
    return nullptr;
}

void HashTableRemove (HashTable *htable, const char *value)
{
    assert (htable              != nullptr);
    assert (htable -> hash_func != nullptr);
    assert (htable -> data      != nullptr);
    assert (value               != nullptr);

    uint64_t hash = htable -> hash_func (value) % htable -> size;

    hashtable_list_remove (htable -> data + hash, value);
}

void hashtable_list_remove (HashTableList *lst, const char *value)
{
    for (size_t index = 0; index < lst -> size; index++)
    {
        if (strcmp (value, lst -> data [index]) == 0)
        {
            lst -> data [index] = lst -> data [--(lst -> size)];
            return;
        }
    }
}

/*
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
*/