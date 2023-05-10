#include "hashfuncs.h"

uint64_t Const1Hash (const char *str)
{
    return 1;
}

uint64_t FirstSymbHash (const char *str)
{
    return *str;
}

uint64_t StrlenHash (const char *str)
{
    return strlen (str);
}

uint64_t LrotrHash (const char *str)
{
    uint64_t hash = 0;

    while (*str != '\0')
    {
        hash = ( (hash >> 1) | (hash << (sizeof (hash) * 8 - 1) ) ) ^ *(str++);
    }

    return hash;
}

uint64_t LrotlHash (const char *str)
{
    uint64_t hash = 0;

    while (*str != '\0')
    {
        hash = ( (hash << 1) | (hash >> (sizeof (hash) * 8 - 1) ) ) ^ *(str++);
    }

    return hash;
}

uint64_t Crc32Hash (const char *str)
{
    uint32_t ret = 0xFFFFFFFF;

    while (*str != '\0')
    {
        ret ^= *(str++);

        for (int i = 0; i < 8; i++)
        {
            ret = (ret & 1) ? (ret >> 1) ^ 0xEDB88320 : ret >> 1;
        }
    }
    return ret;
}