#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_WORD_LEN = 64;


struct HashTableElem
{
    const char *value;
    HashTableElem *next;
};


struct HashTable
{
    size_t (*hash_func)(const char *elem);
    HashTableElem **data;
    size_t size;
};


void HashTableCtor (HashTable *htable, size_t (*hash_func)(const char *elem), size_t size);

void HashTableDtor (HashTable *htable);

void hashtable_list_dtor (HashTableElem *elem);

void HashTableInsert (HashTable *htable, const char *value);

HashTableElem *hashtable_list_insert (HashTableElem *elem, const char *value);

HashTableElem *hashtable_list_find (HashTableElem *elem, const char *value);

const char *HashTableFind (HashTable *htable, const char *value);

#endif