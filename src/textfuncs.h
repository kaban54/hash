#ifndef _TEXT_H
#define _TEXT_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

struct Line
{
    size_t len = 0;
    char *str  = nullptr;
};

struct Text
{
    size_t len    = 0;
    size_t buflen = 0;
    char  *buffer = nullptr; 
    Line  *data   = nullptr;
};

void ReadText (const char *input_file_name, struct Text *txt);

size_t GetSize (FILE *inp_file);

size_t CharReplace (char *str, char ch1, char ch2);

void SetLines (struct Text *txt);

void WriteText (struct Text *txt, FILE *out_file);

void FreeText (struct Text *txt);


#endif