#include "hashtable.h"
#include "hashfuncs.h"
#include "textfuncs.h"

const char *const  INPUT_FILE_NAME = "input.txt";
const char *const OUTPUT_FILE_NAME = "output.csv";

const size_t HASHTABLE_SIZE = 9973;
const size_t NUM_OF_HFUNCS = 6;

void TestHashFuncs (HashTable *hashtables, Text *txt, const char *output_file_name);
void LoadWords     (HashTable *htable, Text *txt);
void PrintListsLen (HashTable *htable, FILE *out_file);

int main ()
{
    Text txt;

    ReadText (INPUT_FILE_NAME, &txt);

    HashTable hashtables [NUM_OF_HFUNCS] = {};

    HashTableCtor (hashtables + 0, Const1Hash,    HASHTABLE_SIZE);
    HashTableCtor (hashtables + 1, FirstSymbHash, HASHTABLE_SIZE);
    HashTableCtor (hashtables + 2, StrlenHash,    HASHTABLE_SIZE);
    HashTableCtor (hashtables + 3, RolHash,       HASHTABLE_SIZE);
    HashTableCtor (hashtables + 4, RorHash,       HASHTABLE_SIZE);
    HashTableCtor (hashtables + 5, Crc32Hash,     HASHTABLE_SIZE);

    TestHashFuncs (hashtables, &txt, OUTPUT_FILE_NAME);

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
        fprintf (out_file, "%ld;", htable -> data [index].size);
    }
    fprintf (out_file, "\n");

    fflush (out_file);
}