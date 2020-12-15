#include <err.h>
#include <stdlib.h>
#include "CHARS.h"

size_t find_char_id(char c, char *lst)
{
    char *p = lst;

    size_t id = 0;
    while (p != 0)
    {
        if (c == lst[id])
            return id;
        id += 1;
    }
    errx(1, "The character '%c' is not in CHARS",c);
    return CHARSLEN;
};
