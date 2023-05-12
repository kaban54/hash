#include "hashtable.h"
#include "hashfuncs.h"
#include "textfuncs.h"
#include <time.h>

const char *const  input_file_name = "input.txt";

const size_t HASHTABLE_SIZE = 9973;
const size_t NUM_OF_OPS     = 20000000;


void HashTableSpeedTest (HashTable *htable, Text *txt);
void LoadWords     (HashTable *htable, Text *txt);

int main ()
{
    Text txt;
    ReadText (input_file_name, &txt);

    HashTable htable = {};
    HashTableCtor (&htable, Crc32Intrin, HASHTABLE_SIZE);

    LoadWords (&htable, &txt);

    HashTableSpeedTest (&htable, &txt);

    FreeText (&txt);

    return 0;
}

void HashTableSpeedTest (HashTable *htable, Text *txt)
{
    assert (htable != nullptr);
    assert (txt    != nullptr);

    clock_t start = clock ();

    for (size_t index = 0; index < NUM_OF_OPS; index += 1)
    {
        HashTableFind (htable, txt -> data [index % txt -> len].str);
    }

    clock_t end = clock ();

    printf ("%ld find operations done.\ntime = %lfs\n", NUM_OF_OPS, (double)(end - start) / CLOCKS_PER_SEC);
}

void LoadWords (HashTable *htable, Text *txt)
{
    assert (htable != nullptr);
    assert (txt    != nullptr);

    for (size_t index = 0; index < txt -> len; index += 2)
    {
        HashTableInsert (htable, txt -> data [index].str);
    }
}