#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct HashTableElem
{
    const char *value;
    HashTableElem *next;
};


struct HashTable
{
    uint64_t (*hash_func)(const char *elem);
    HashTableElem **data;
    uint64_t size;
};


void HashTableCtor (HashTable *htable, uint64_t (*hash_func)(const char *elem), uint64_t size);

void HashTableDtor (HashTable *htable);

void hashtable_list_dtor (HashTableElem *elem);

void HashTableInsert (HashTable *htable, const char *value);

HashTableElem *hashtable_list_insert (HashTableElem *elem, const char *value);

HashTableElem *hashtable_list_find (HashTableElem *elem, const char *value);

const char *HashTableFind (HashTable *htable, const char *value);

void HashTableDelete (HashTable *htable, const char *value);

HashTableElem *hashtable_list_delete (HashTableElem *elem, const char *value);

#endif