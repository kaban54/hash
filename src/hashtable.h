#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" int64_t mystrcmp (const char *str1, const char *str2);

const size_t LIST_BASE_CAP = 4;

struct HashTableList 
{
    size_t size;
    size_t capacity;
    
    const char **data;
};

struct HashTable
{
    uint64_t (*hash_func)(const char *elem);
    HashTableList *data;
    uint64_t size;
};


void HashTableCtor (HashTable *htable, uint64_t (*hash_func)(const char *elem), uint64_t size);

void hashtable_list_ctor (HashTableList *lst, size_t capacity);

void HashTableDtor (HashTable *htable);

void hashtable_list_dtor (HashTableList *lst);

void HashTableInsert (HashTable *htable, const char *value);

void hashtable_list_insert (HashTableList *lst, const char *value);

void hashtable_list_resize (HashTableList *lst, size_t new_cap);

const char *HashTableFind (HashTable *htable, const char *value);

const char *hashtable_list_find (HashTableList *lst, const char *value);

void HashTableRemove (HashTable *htable, const char *value);

void hashtable_list_remove (HashTableList *lst, const char *value);

//inline HashTableElem *hashtable_list_find_asm (HashTableElem *elem, const char *value);

#endif