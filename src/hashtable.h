#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const size_t MAX_WORD_LEN = 64;


struct HashTableElem
{
    char value [MAX_WORD_LEN];
    HashTableElem *next;
};


struct HashTable
{
    size_t (*hash)(const char *elem);
    HashTableElem **data;
    size_t size;
};


void HashTableCtor (HashTable *htable, size_t (*hash_func)(const char *elem), size_t size);

void HashTableDtor (HashTable *htable);

void hashtable_list_dtor (HashTableElem *elem);

#endif