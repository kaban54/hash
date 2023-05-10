#ifndef _HASHFUNCS_H
#define _HASHFUNCS_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t Const1Hash    (const char *str);
uint64_t FirstSymbHash (const char *str);
uint64_t StrlenHash    (const char *str);
uint64_t RorHash       (const char *str);
uint64_t RolHash       (const char *str);
uint64_t Crc32Hash     (const char *str);

#endif