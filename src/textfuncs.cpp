#include "textfuncs.h"

void ReadText (const char *input_file_name, struct Text *txt)
{    
    assert (input_file_name != nullptr);
    assert (txt             != nullptr);

    FILE *inp_file = fopen (input_file_name, "r");
    assert (inp_file != nullptr);

    size_t filesize = GetSize (inp_file);

    txt -> buffer = (char *) calloc (filesize + 1, sizeof((txt -> buffer)[0]));
    assert (txt -> buffer != nullptr);

    txt -> buflen = fread (txt -> buffer, sizeof((txt -> buffer)[0]), filesize, inp_file);
    *(txt -> buffer + txt -> buflen) = '\0';
    
    fclose (inp_file);

    txt -> len = CharReplace (txt -> buffer, '\n', '\0') + 1;

    SetLines (txt);
}

size_t GetSize (FILE *inp_file)
{
    if (inp_file == nullptr) return 0;
    struct stat stat_buf = {};

    fstat (fileno (inp_file), &stat_buf);
    return stat_buf.st_size;
}

size_t CharReplace (char *str, char ch1, char ch2)
{
    if (str == nullptr) return 0;

    size_t count = 0;
    str = strchr (str, ch1);

    while (str != nullptr)
    {
        count++;
        *str = ch2;
        str = strchr (str + 1, ch1);
    }

    return count;
}

void SetLines (struct Text *txt)
{
    assert (txt != nullptr);

    txt -> data = (struct Line*) calloc (txt -> len, sizeof ((txt -> data)[0]));
    assert (txt -> data != nullptr);

    char *str_ptr = txt -> buffer;
    size_t length = 0;

    for (size_t index = 0; index < txt -> len; index++)
    {
        length = strlen (str_ptr);

        strncpy ((txt -> data + index) -> str, str_ptr, MAX_STR_LEN);
        (txt -> data + index) -> len =  length;

        str_ptr += length + 1;
    }
}


void WriteText (struct Text *txt, FILE *out_file)
{
    assert (txt      != nullptr);
    assert (out_file != nullptr);

    for (size_t index = 0; index < txt -> len; index++)
    {
        fputs ((txt -> data + index) -> str, out_file);
        //fputc ('\r', out_file);
        fputc ('\n', out_file);
    }
}

void FreeText (struct Text *txt)
{
    free (txt -> buffer);
    free (txt ->   data);
}