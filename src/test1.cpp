#include "hashtable.h"


int main ()
{

}

size_t Const1Hash (const char *str)
{
    return 1;
}

size_t FirstSymbHash (const char *str)
{
    return *str;
}

size_t StrlenHash (const char *str)
{
    return strlen (str);
}

size_t LrotrHash (const char *str)
{
    size_t hash = 0;

    while (*str != '\0')
    {
        hash = ( (hash >> 1) | (hash << (sizeof (hash) * 8 - 1) ) ) ^ *(str++);
    }

    return hash;
}

size_t LrotlHash (const char *str)
{
    size_t hash = 0;

    while (*str != '\0')
    {
        hash = ( (hash << 1) | (hash >> (sizeof (hash) * 8 - 1) ) ) ^ *(str++);
    }

    return hash;
}