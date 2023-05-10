# TITLE

## Исследование и сравнение хеш-функций

В этой части работы оценивалась пригодность различных хеш-функций для хеширования английскиих слов и использования в хеш-таблице с цепочками.

### Исследуемые функци

#### 1. Const1Hash

Функция, всегда возвращаающая 1.

```C
uint64_t Const1Hash (const char *str)
{
    return 1;
}
```

#### 2. FirstSymbHash

Функция, возвращающая ASCII-код первого символа.

```C
uint64_t FirstSymbHash (const char *str)
{
    return *str;
}
```

#### 3. StrlenHash

Функция, возвращающая длину строки.

```C
uint64_t StrlenHash (const char *str)
{
    return strlen (str);
}
```
#### 4. RorHash

На каждом шаге значение хеша циклически сдвигается вправо, после чего делается xor с ASCII-кодом следующего символа.

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

#### 5. RolHash

То же, что и RorHash, но сдвиг делается влево.

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

#### 6. [Crc32](https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%A6%D0%B8%D0%BA%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B8%D0%B7%D0%B1%D1%8B%D1%82%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4)

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

### Входные данные

Для исследования функций в хеш-таблицу было загружено около 104316 различных английских слов.\
Размер хеш таблицы — 9973.\
Таким образом средняя длина цепочки равна 10,46.

### Ход работы

Для каждой функции построим график зависимости длины цепочки от хеша и посчитаем стандартное отклонение длины цепочки:

#### 1. Const1Hash

Стандартное отклонение: 1044,57

#### 2. FirstSymbHash

Стандартное отклонение: 212,84

#### 3. StrlenHash

Стандартное отклонение: 348,18

#### 4. RorHash

Стандартное отклонение: 5,38

#### 5. RolHash

Стандартное отклонение: 12,35

#### 6. Crc32

Стандартное отклонение: 3,25

| Функция       | Стандартное отклонение |
|---------------|------------------------|
| Const1Hash    | 1044,57                |
| FirstSymbHash | 212,84                 |
| StrlenHash    | 348,18                 |
| RorHash       | 5,38                   |
| RolHash       | 12,35                  |
| Crc32         | 3,25                   |
