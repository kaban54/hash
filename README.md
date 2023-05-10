# TITLE

## Исследование и сравнение хеш-функций

В этой части работы оценивалась пригодность различных хеш-функций для хеширования английскиих слов и использования в хеш-таблице с цепочками.

### Исследуемые функци

1. Функция, всегда возвращаающая 1.

```C
uint64_t Const1Hash (const char *str)
{
    return 1;
}
```

2. Функция, возвращающая ASCII-код первого символа.

```C
uint64_t FirstSymbHash (const char *str)
{
    return *str;
}
```

3. Функция, возвращающая длину строки.

```C
uint64_t StrlenHash (const char *str)
{
    return strlen (str);
}
```
4. RorHash

```C
uint64_t RorHash (const char *str)
{
    uint64_t hash = 0;

    while (*str != '\0')
    {
        hash = ( (hash >> 1) | (hash << (sizeof (hash) * 8 - 1) ) ) ^ *(str++);
    }

    return hash;
}
```

5. RolHash

```C
uint64_t RolHash (const char *str)
{
    uint64_t hash = 0;

    while (*str != '\0')
    {
        hash = ( (hash << 1) | (hash >> (sizeof (hash) * 8 - 1) ) ) ^ *(str++);
    }

    return hash;
}
```

6. Crc32

```C
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
```

### Ход работы

Для каждой функции построим график зависимости длины цепочки от хеша:


