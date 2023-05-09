#include "hashtable.h"
#include "hashfuncs.h"
#include "textfuncs.h"

const char *const  input_file_name = "input.txt";
const char *const output_file_name = "test1out.csv";

const size_t HASHTABLE_SIZE = 9973;
const size_t NUM_OF_HFUNCS = 6;

void TestHashFuncs (HashTable *hashtables, Text *txt, const char *output_file_name);
void LoadWords     (HashTable *htable, Text *txt);
void PrintListsLen (HashTable *htable, FILE *out_file);

int main ()
{
    Text txt;

    ReadText (input_file_name, &txt);

    HashTable hashtables [NUM_OF_HFUNCS] = {};

    HashTableCtor (hashtables + 0, Const1Hash,    HASHTABLE_SIZE);
    HashTableCtor (hashtables + 1, FirstSymbHash, HASHTABLE_SIZE);
    HashTableCtor (hashtables + 2, StrlenHash,    HASHTABLE_SIZE);
    HashTableCtor (hashtables + 3, LrotlHash,     HASHTABLE_SIZE);
    HashTableCtor (hashtables + 4, LrotrHash,     HASHTABLE_SIZE);
    HashTableCtor (hashtables + 5, Crc32Hash,     HASHTABLE_SIZE);

    TestHashFuncs (hashtables, &txt, output_file_name);

    for (size_t index = 0; index < NUM_OF_HFUNCS; index++) HashTableDtor (hashtables + index);

    FreeText (&txt);

    return 0;
}

void TestHashFuncs (HashTable *hashtables, Text *txt, const char *output_file_name)
{
    assert (hashtables       != nullptr);
    assert (txt              != nullptr);
    assert (output_file_name != nullptr);

    FILE *out_file = fopen (output_file_name, "w");
    assert (out_file != nullptr);

    for (size_t index = 0; index < NUM_OF_HFUNCS; index++)
    {
        LoadWords     (hashtables + index, txt);
        PrintListsLen (hashtables + index, out_file);
    }

    fclose (out_file);
}

void LoadWords (HashTable *htable, Text *txt)
{
    assert (htable != nullptr);
    assert (txt    != nullptr);

    for (size_t index = 0; index < txt -> len; index++)
    {
        HashTableInsert (htable, txt -> data [index].str);
    }
}

void PrintListsLen (HashTable *htable, FILE *out_file)
{
    assert (htable   != 0);
    assert (out_file != 0);

    for (size_t index = 0; index < htable -> size; index++)
    {
        size_t len = GetListLen (htable -> data [index]);
        fprintf (out_file, "%lld;", len);
    }
    fprintf (out_file, "\n");

    fflush (out_file);
}